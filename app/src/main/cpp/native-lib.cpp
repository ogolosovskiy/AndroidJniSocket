#include <jni.h>
#include <string>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_oleggl_jnitest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    char hello[255] = "Hello from C++";

    int _socket;
    sockaddr_in* _server;

    if ((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        sprintf(hello, "socket() failed: %s\n", strerror(errno));
        return env->NewStringUTF(hello);
    }

    _server = new sockaddr_in();

    memset((char *)_server, 0, sizeof(sockaddr_in));
    _server->sin_family = AF_INET;
    _server->sin_port = htons(7777);
    inet_pton(AF_INET, "67.209.115.215", &(_server->sin_addr));


    int test = 0xАА;


    if (::setsockopt(_socket, IPPROTO_IP, IP_TOS, &test, sizeof(test)) < 0)
    {
        sprintf(hello, "setsockopt() failed: %s\n", strerror(errno));
        return env->NewStringUTF(hello);
    }

    //send the message
    std::string str("test");
    if (sendto(_socket, str.c_str(), str.size(), 0, (struct sockaddr *) _server, sizeof(sockaddr_in)) == -1)
    {
        sprintf(hello, "sendto() failed: %s\n", strerror(errno));
        return env->NewStringUTF(hello);
    }


    return env->NewStringUTF(hello);
}
