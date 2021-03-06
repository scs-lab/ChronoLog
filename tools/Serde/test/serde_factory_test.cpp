//
// Created by kfeng on 12/6/21.
//

#include <SerDe.h>

int main()
{
//    SerDeFactory sdf = SerDeFactory();
//    auto serde_ = sdf.create(SerDeType::CEREAL);
    SerDeFactory *serde_manager = new SerDeFactory(SerDeType::CEREAL);
    SerDe *serde = serde_manager->getSerDe();

    {
        ClientMessage clientMsg;
        std::unique_ptr<std::ostringstream> oss;
        clientMsg.msgType_ = ClientMessage::CONNECTION;
        oss = serde->serializeClientMessage(clientMsg);
        std::cout << "Serialized client msg (len: " << std::to_string(oss->str().length()) << "): "
                  << oss->str() << std::endl;

        std::unique_ptr<ClientMessage> clientMsg2 = serde->deserializeClientMessage(reinterpret_cast<unsigned char *>(const_cast<char *>(oss->str().data())), oss->str().length());
        std::cout << "Deserialized client msg: " << *clientMsg2 << std::endl;
    }

    {
        ServerMessage serverMsg;
        std::unique_ptr<std::ostringstream> oss;
        serverMsg.msgType_ = ServerMessage::CONNRESPONSE;
        serverMsg.timeInfo_ = TimeInfo("203984952375", 0.00001235);
        std::vector<ChronoKeeperInfo> chronoKeeperList;
        for (int i = 0; i < 3; i++) {
            ChronoKeeperInfo chronoKeeperInfo(std::string("172.25.101.") + std::to_string(i + 1), 8000 + i);
            chronoKeeperList.push_back(chronoKeeperInfo);
        }
        serverMsg.chronoKeeperList_ = chronoKeeperList;
        oss = serde->serializeServerMessage(serverMsg);
        std::cout << "Serialized server msg (len: " << std::to_string(oss->str().length()) << "): "
                  << oss->str() << std::endl;

        std::unique_ptr<ServerMessage> serverMsg2 = serde->deserializeServerMessage(reinterpret_cast<unsigned char *>(const_cast<char *>(oss->str().data())), oss->str().length());
        std::cout << "Deserialized server msg: " << *serverMsg2 << std::endl;
    }
}