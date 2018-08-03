#ifndef UDPSERVER_H
#define	UDPSERVER_H

#include <map>
#include <string>
#include "StudentMap.h"
#include "BookMap.h"
#include "DigiLibMap.h"
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>


class UdpServer {
public:
  UdpServer(boost::asio::io_service &io_service);
  ~UdpServer();

protected:
  void onReceive(boost::system::error_code ec, std::size_t bytes_received);
  void doReceive();
  void parseMessage(std::string const &message, boost::asio::ip::udp::endpoint const &sender);

  void registerClient(std::string const &clientName, boost::asio::ip::udp::endpoint const &sender);
  template<class input>
  void sendMessageToClients(input const &text);
  int convertStringToInt(std::string &num);
  void adminData(int &taskId, std::vector<std::string> &vec);
  void studentData(int &taskId, std::vector<std::string> & vec);
  void processData(std::vector<std::string> vec);
  std::vector<std::string> parseData(std::string s);
  template<typename Out>
  void split(const std::string &s, char delim, Out result);

  template<class input>
  void serializeData(input &vector);
private:
  // a reference to a more global io service object
  boost::asio::io_service &m_ioService;

  //! this will contain the used udp socket
  boost::asio::ip::udp::socket m_socket;

  //! this will map the clients name to the registered endpoint for this client
  std::map<std::string, boost::asio::ip::udp::endpoint> m_registeredClients;

  static const int c_serverPort = 2000;

  static const int c_maxLength = 255;
  std::array<char, c_maxLength> m_buffer;

  boost::asio::ip::udp::endpoint m_senderEndpoint;
  StudentMap m_studentMap;
  BookMap m_bookMap;
  DigiLibMap m_digiLibMap;


};

#endif	/* UDPSERVER_H */

