#include <game/core.h>

#if (CURRENT_PLATFORM == PLATFORM_LINUX)

#include <game/platform/linux/renderer.h>

namespace punkyoi::platform::linux {

    PlatformRenderer::PlatformRenderer() {
    }

    PlatformRenderer::~PlatformRenderer() {
    }

    void PlatformRenderer::init(::punkyoi_api::IWindow* window) {
        log::console() << "Initializing renderer" << log::endl;
        m_window = window;
        // configure VAO/VBO
        unsigned int VBO;
        float vertices[] = { 
            // pos      // tex
            -0.5f, 0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 
        
            -0.5f, 0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &m_quadVAO);
        glGenBuffers(1, &VBO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(m_quadVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);  
        glBindVertexArray(0);

        m_currentShader = createShader(
            R"(
                #version 330 core
                layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

                out vec2 TexCoords;

                uniform mat4 model;

                void main()
                {
                    TexCoords = vec2(vertex.z, 1.0 - vertex.w);
                    gl_Position = model * vec4(vertex.xy, 0.0, 1.0);
                }
            )",
            R"(
                #version 330 core
                in vec2 TexCoords;
                out vec4 color;

                uniform sampler2D image;
                uniform vec3 spriteColor;

                void main()
                {    
                    color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
                }
            )");
        glUseProgram(m_currentShader);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_windowRatio = vec2(1.0, float(m_window->getWidth()) / m_window->getHeight());
    }

    void PlatformRenderer::deinit() {
        log::console() << "Deinitializing renderer" << log::endl;
        glDeleteVertexArrays(1, &m_quadVAO);
        glUseProgram(0);
    }

    void PlatformRenderer::onRenderPre() {
        if (m_windowRatio != vec2(1.0, float(m_window->getWidth()) / m_window->getHeight())) {
            m_windowRatio = vec2(1.0, float(m_window->getWidth()) / m_window->getHeight());
            glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
        }
        m_matrices.push_back(mat4({ m_windowRatio.x, 0, 0, 0,
                                    0, m_windowRatio.y, 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1}
                                    ));
    }

    void PlatformRenderer::onRenderPost() {
        m_matrices.clear();
    }

    void PlatformRenderer::push() {
        m_matrices.push_back(mat4({ 1, 0, 0, 0,
                                    0, 1, 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1}
                                    ));
    }

    void PlatformRenderer::pop() {
        m_matrices.pop_back();
    }

    void PlatformRenderer::translate(vec2 origin) {
        m_matrices.back()[3][0] += origin.x;
        m_matrices.back()[3][1] += origin.y;
    }

    void PlatformRenderer::scale(vec2 scale) {
        m_matrices.back()[0][0] *= scale.x;
        m_matrices.back()[1][1] *= scale.y;
    }

    void PlatformRenderer::rotate(float angle) {
    }

    void PlatformRenderer::drawImage(::punkyoi_api::IImage& image) {
        if (!m_texturesMap.count(image.getBuffer())) {
            unsigned int id;
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getBuffer());
            // set Texture wrap and filter modes
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // unbind texture
            glBindTexture(GL_TEXTURE_2D, 0);
            m_texturesMap[image.getBuffer()] = id;
        }


        unsigned int texture = m_texturesMap[image.getBuffer()];

        mat4 model = mat4({ 1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1});

        for (mat4& it : m_matrices) {
            model = it * model;
        }

        glUniformMatrix4fv(glGetUniformLocation(m_currentShader, "model"), 1, false, &(model)[0][0]);
        glUniform3f(glGetUniformLocation(m_currentShader, "spriteColor"), 1, 1, 1);
    
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(m_currentShader, "texture"), 0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(m_quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    PlatformRenderer::Shader PlatformRenderer::createShader(std::string vertexText, std::string fragmentText) {
        unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexChar = vertexText.c_str();
        glShaderSource(vertexId, 1, &vertexChar, NULL);
        glCompileShader(vertexId);

        GLint result;
        glGetShaderiv(vertexId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            GLint length;
            glGetShaderiv(vertexId, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(vertexId, length, &length, &error[0]);
            log::console() << std::string(error.data()) << log::endl;
            glDeleteShader(vertexId);

            return 0;
        }

        unsigned int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentChar = fragmentText.c_str();
        glShaderSource(fragmentId, 1, &fragmentChar, NULL);
        glCompileShader(fragmentId);

        glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            GLint length;
            glGetShaderiv(fragmentId, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(fragmentId, length, &length, &error[0]);
            log::console() << std::string(error.data()) << log::endl;
            glDeleteShader(fragmentId);

            return 0;
        }

        PlatformRenderer::Shader programId = glCreateProgram();
        glAttachShader(programId, vertexId);
        glAttachShader(programId, fragmentId);
        glLinkProgram(programId);
        glValidateProgram(programId);
        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);

        return programId;
    }

}

#endif