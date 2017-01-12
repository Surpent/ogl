#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <glfw3.h>

// GLMをインクルード
#include <glm/glm.hpp>
using namespace glm;

int main() {
    // GLFWを初期化
    if (!glfwInit())
    {
        fprintf( stderr, "GLFWの初期化に失敗しました。n");
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x アンチエイリアス
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL3.3を使います。
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS用：必ずしも必要ではありません。
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 古いOpenGLは使いません。
    
    // Windowを開き、OpenGLコンテキストを作ります
    GLFWwindow* window; // (ソースコードではこの変数はグローバルです。)
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "GLFWウィンドウのオープンに失敗しました。 もしIntelのGPUならば, 3.3に対応していません。チュートリアルのバージョン2.1を試してください。n" );
        glfwTerminate();
        return -1;
    }
    
    
    glfwMakeContextCurrent(window); // GLEWを初期化する
    glewExperimental=true; // コアプロファイルで必要となります。
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEWの初期化に失敗しました。n");
        return -1;
    }
    
    // 下でエスケープキーが押されるのを捉えるのを保証します。
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    do{
        // 何も描きません。チュートリアル2で会いましょう！
        
        // バッファをスワップする。
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // ESCキーが押されたかウィンドウが閉じたかをチェックする。
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
}
