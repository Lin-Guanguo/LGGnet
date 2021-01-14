#include "../../easyLA/tool/Log.h"
#include "../../easyLA/tool/ClientSocket.h"

using namespace std;
using namespace LGG;

int main() {
    auto connect = ClientSocket::connect("127.0.0.1", 8011);
    connect.write("socket client message\n");
    auto line = connect.readLine();
    LOG_INFO("readline = ", line);
}