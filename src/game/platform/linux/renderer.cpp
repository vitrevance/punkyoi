#include <game/core.h>

#if (CURRENT_PLATFORM == PLATFORM_LINUX)

#include <game/platform/linux/renderer.h>

namespace punkyoi::platform::linux {

    PlatformRenderer::PlatformRenderer() {
    }

    PlatformRenderer::~PlatformRenderer() {
    }

    void PlatformRenderer::init(::punkyoi_api::IWindow*) {
        log::console() << "Initializing renderer" << log::endl;
        // configure VAO/VBO
        unsigned int VBO;
        float vertices[] = { 
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 
        
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
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
                uniform mat4 projection;

                void main()
                {
                    TexCoords = vertex.zw;
                    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
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
    }

    void PlatformRenderer::deinit() {
        log::console() << "Deinitializing renderer" << log::endl;
        glDeleteVertexArrays(1, &m_quadVAO);
        glUseProgram(0);
    }

    void PlatformRenderer::onRenderPre() {}
    void PlatformRenderer::onRenderPost() {}

    void PlatformRenderer::push() {}
    void PlatformRenderer::pop() {}
    void PlatformRenderer::translate(vec2 origin) {}
    void PlatformRenderer::scale(vec2 scale) {}
    void PlatformRenderer::rotate(float angle) {}
    void PlatformRenderer::drawImage(const ::punkyoi_api::IImage& image) {}

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