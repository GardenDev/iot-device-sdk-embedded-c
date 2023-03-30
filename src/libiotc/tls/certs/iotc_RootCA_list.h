/* Copyright 2018-2020 Google LLC
 *
 * This is part of the Google Cloud IoT Device SDK for Embedded C.
 * It is licensed under the BSD 3-Clause license; you may not use this file
 * except in compliance with the License.
 *
 * You may obtain a copy of the License at:
 *  https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __IOTC_ROOTCA_LIST_H__
#define __IOTC_ROOTCA_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	const char *domain;
	unsigned short port;
	const unsigned char *ca;
	unsigned short ca_len;
	const char *username;
} UltronMQTTServerInfo_t;

#define GCP_MQTT_LTS_DOMAIN			"mqtt.2030.ltsapis.goog"
#define GCP_MQTT_PORT_NUM			8883

#define ClearBlade_MQTT_LTS_DOMAIN	"asia-east1-mqtt.clearblade.com"
#define ClearBlade_MQTT_PORT_NUM	8883

extern unsigned char gcp_RootCA_list[];
extern unsigned char clearblade_RootCA_list[];

extern UltronMQTTServerInfo_t mqtt_server_info;

#if 0
#ifndef IOTC_ROOTCA_LIST_BYTE_LENGTH
#define IOTC_ROOTCA_LIST_BYTE_LENGTH 1389
#endif /* IOTC_ROOTCA_LIST_BYTE_LENGTH */

extern unsigned char iotc_RootCA_list[IOTC_ROOTCA_LIST_BYTE_LENGTH];
#endif

#ifdef __cplusplus
}
#endif

#endif /* __IOTC_ROOTCA_LIST_H__ */
