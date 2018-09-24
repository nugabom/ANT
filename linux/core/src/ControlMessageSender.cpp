/* Copyright 2017-2018 All Rights Reserved.
 *  Gyeonghwan Hong (redcarrottt@gmail.com)
 *
 * [Contact]
 *  Gyeonghwan Hong (redcarrottt@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0(the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../inc/ControlMessageSender.h"

#include "../inc/API.h"

#include <iostream>
#include <string>
#include <string.h>

using namespace sc;

void ControlMessageSender::send_control_message(std::string &message) {
  int message_buffer_size = message.size() + 1;
  char *message_buffer = new char[message_buffer_size];
  strncpy(message_buffer, message.c_str(), message_buffer_size);
  message_buffer[message_buffer_size - 1] = '\0';
  int res = Core::singleton()->send(message_buffer, message_buffer_size, true);
}

void ControlMessageSender::send_request(CMCode request_code, int adapter_id) {
  std::string message("");

  // Write first line (request code)
  message.append(std::to_string(request_code));
  message.append("\n");

  // Write second line (adapter ID)
  message.append(std::to_string(adapter_id));

  // Send the message
  this->send_control_message(message);
}

void ControlMessageSender::send_request_connect(int adapter_id) {
  this->send_request(CMCode::kCMCodeConnect, adapter_id);
  LOG_VERB("Send(Control Msg): Request(Connect %d)", adapter_id);
}

void ControlMessageSender::send_request_disconnect(int adapter_id) {
  this->send_request(CMCode::kCMCodeDisconnect, adapter_id);
  LOG_VERB("Send(Control Msg): Request(Disconnect %d)", adapter_id);
}

void ControlMessageSender::send_request_disconnect_ack(int adapter_id) {
  this->send_request(CMCode::kCMCodeDisconnectAck, adapter_id);
  LOG_VERB("Send(Control Msg): Request(DisconnectAck %d)", adapter_id);
}

void ControlMessageSender::send_request_sleep(int adapter_id) {
  this->send_request(CMCode::kCMCodeSleep, adapter_id);
  LOG_VERB("Send(Control Msg): Request(Sleep %d)", adapter_id);
}

void ControlMessageSender::send_request_wake_up(int adapter_id) {
  this->send_request(CMCode::kCMCodeWakeUp, adapter_id);
  LOG_VERB("Send(Control Msg): Request(WakeUp %d)", adapter_id);
}

void ControlMessageSender::send_noti_private_data(PrivType priv_type,
                                                  char *priv_data_buffer,
                                                  uint32_t priv_data_length) {
  std::string message("");

  // Write first line (request code)
  message.append(std::to_string(CMCode::kCMCodePriv));
  message.append("\n");

  // Write second line (priv type)
  message.append(std::to_string(priv_type));
  message.append("\n");

  // Write third+ line (priv data)
  message.append(priv_data_buffer, priv_data_length);

  // Send the message
  this->send_control_message(message);
  LOG_VERB("Send(Control Msg): Request(Priv %d)\n%s", priv_type, priv_data_buffer);
}