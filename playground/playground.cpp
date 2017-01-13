#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <glfw3.h>

// GLMをインクルード
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>


int main()
{
    // GLFWを初期化
    if (!glfwInit())
    {
        fprintf( stderr, "GLFWの初期化に失敗しました。n");
        return -1;
    }
    
    // 4x アンチエイリアス
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    // OpenGL3.3を使います。
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    // MacOS用：必ずしも必要ではありません。
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // 古いOpenGLは使いません。
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Windowを開き、OpenGLコンテキストを作ります
    GLFWwindow* window; // (ソースコードではこの変数はグローバルです。)
    window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red Triangle", NULL, NULL);
    
    if( window == NULL )
    {
        fprintf( stderr, "GLFWウィンドウのオープンに失敗しました。 もしIntelのGPUならば, 3.3に対応していません。チュートリアルのバージョン2.1を試してください。n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // GLEWを初期化する
    glewExperimental = true; // コアプロファイルで必要となります。
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEWの初期化に失敗しました。n");
        getchar();
        glfwTerminate();
        return -1;
    }
    // 下でエスケープキーが押されるのを捉えるのを保証します。
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    // 配列バッファオブジェクト(Vertex Array Object)を初期化
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    
    
    // 3頂点を表す3つのベクトルの配列
    // スクリーン座標
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    
    // これが頂点バッファを指し示すものとなります。
    GLuint vertexbuffer;
    
    // バッファを1つ作り、vertexbufferに結果IDを入れます。
    glGenBuffers(1, &vertexbuffer);
    
    // 次のコマンドは'vertexbuffer'バッファについてです。
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
    // 頂点をOpenGLに渡します。
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    

    
    do{
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );
        
        // Use our shader
        glUseProgram(programID);
        
        // 最初の属性バッファ：頂点
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // 属性0：0に特に理由はありません。しかし、シェーダ内のlayoutとあわせないといけません。
            3,                  // サイズ
            GL_FLOAT,           // タイプ
            GL_FALSE,           // 正規化？
            0,                  // ストライド
            (void*)0            // 配列バッファオフセット
        );
        
        // 三角形を描きます！
        glDrawArrays(GL_TRIANGLES, 0, 3); // 頂点0から始まります。合計3つの頂点です。&rarr;1つの三角形です。
        
        glDisableVertexAttribArray(0);

        
        // バッファをスワップする。
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // ESCキーが押されたかウィンドウが閉じたかをチェックする。
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
}
