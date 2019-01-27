
#include <WebClient.h>

int WebClient::connect(IPAddress ip, uint16_t port){
        return 0;
}
int WebClient::connect(const char *host, uint16_t port){
        return 0;
}
size_t WebClient::write(uint8_t) {
        return 0;
}
size_t WebClient::write(const uint8_t *buf, size_t size){
        return 0;
}
int WebClient::available(){
        return 0;
}
int WebClient::read() {
        return 0;
}
int WebClient::read(uint8_t *buf, size_t size){
        return 0;
}
int WebClient::peek() {
        return 0;
}
void WebClient::flush(){

}
void WebClient::stop() {
};
uint8_t WebClient::connected(){
        return 0;
}
WebClient::operator bool(){
        return false;
}
