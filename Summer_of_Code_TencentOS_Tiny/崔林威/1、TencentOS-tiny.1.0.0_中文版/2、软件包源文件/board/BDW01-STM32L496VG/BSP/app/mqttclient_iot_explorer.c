#include "stm32l4xx_hal.h"
#include "mcu_init.h"
#include "tos_k.h"
#include "mqttclient.h"
#include "cjson.h"
#include "sal_module_wrapper.h"



//#define USE_ESP8266
//#define USE_NB_BC35
//#define USE_BC26
//#define USE_EC200S
#define USE_M5313


#if defined(USE_ESP8266)
#include "esp8266.h"
#elif defined(USE_BC26)
#include "bc26.h"
#elif defined(USE_EC200S)
#include "ec200s.h"
#elif defined(USE_M5313)
#include "m5313.h"

#endif

uint8_t module_sel=0;	//0---M5313; 1---wifi;  2---BT;  3---Lora


#ifdef USE_ESP8266 
static hal_uart_port_t esp8266_port = HAL_UART_PORT_0;

void mqtt_set_esp8266_port(hal_uart_port_t port) {
    esp8266_port = port;
}
#endif

k_event_t report_result_event;
k_event_flag_t report_success = 1<<0;
k_event_flag_t report_fail    = 1<<1;

static void tos_topic_handler(void* client, message_data_t* msg)
{
    (void) client;
    cJSON* cjson_root   = NULL;
    cJSON* cjson_status = NULL;
    char* status = NULL;
    k_event_flag_t event_flag = report_fail;

    /* 打印日志 */
    MQTT_LOG_I("-----------------------------------------------------------------------------------");
    MQTT_LOG_I("%s:%d %s()...\ntopic: %s, qos: %d. \nmessage:\n\t%s\n", __FILE__, __LINE__, __FUNCTION__, 
            msg->topic_name, msg->message->qos, (char*)msg->message->payload);
    MQTT_LOG_I("-----------------------------------------------------------------------------------\n");
    
    /* 使用cjson解析上报响应数据 */
    cjson_root = cJSON_Parse((char*)msg->message->payload);
    if (cjson_root == NULL) {
        printf("report reply message parser fail\r\n");
        event_flag = report_fail;
        goto exit;
    }
    
    /* 提取status状态 */
    cjson_status = cJSON_GetObjectItem(cjson_root, "status");
    status = cJSON_GetStringValue(cjson_status);
    if (cjson_status == NULL || status == NULL) {
        printf("report reply status parser fail\r\n");
        event_flag = report_fail;
        goto exit;
    }
    
    /* 判断status状态 */
    if (strstr(status,"success")) {
        event_flag = report_success;
    }else {
        event_flag = report_fail;
    }
    
exit:
    cJSON_Delete(cjson_root);
    cjson_root = NULL;
    status = NULL;
    
    tos_event_post(&report_result_event, event_flag);
    
    return;
}

#define REPORT_DATA_TEMPLATE "{\"method\":\"report\",\"clientToken\":\"00000001\",\"params\":{\"brightness\":%d,\"name\":\"bedroom\"}}"

char report_buf[200];

void mqttclient_task(void)
{
    int error;
    
    int lightness = 0;
    
    mqtt_client_t *client = NULL;
    
    mqtt_message_t msg;
    
    k_event_flag_t match_flag;
    
    char  host_ip[20];
    
    memset(&msg, 0, sizeof(msg));
    
#ifdef USE_ESP8266 
    esp8266_sal_init(esp8266_port);
    esp8266_join_ap("Supowang", "13975428888");
#endif

#ifdef USE_NB_BC35
    int bc35_28_95_sal_init(hal_uart_port_t uart_port);
    bc35_28_95_sal_init(HAL_UART_PORT_0);
#endif

#ifdef USE_BC26
    bc26_sal_init(HAL_UART_PORT_2);
#endif

#ifdef USE_EC200S
    ec200s_sal_init(HAL_UART_PORT_2);
#endif

#ifdef USE_M5313
	m5313_sal_init(HAL_UART_PORT_2);
#endif

    mqtt_log_init();

    client = mqtt_lease();
    
    tos_event_create(&report_result_event, (k_event_flag_t)0u);
    
    /* Domain Format: <your product ID>.iotcloud.tencentdevices.com */
    tos_sal_module_parse_domain("S7271EG5D8.iotcloud.tencentdevices.com",host_ip,sizeof(host_ip));
    
    /*
        These infomation is generated by mqtt_config_gen.py tool in "TencentOS-tiny\tools" directory.
    */
    mqtt_set_port(client, "1883");
    mqtt_set_host(client, host_ip);
    mqtt_set_client_id(client, "S7271EG5D8bdw01_led");
    mqtt_set_user_name(client, "S7271EG5D8bdw01_led;21010406;12365;4294967295");
    mqtt_set_password(client, "5b5d6b05117634f199e65fb078acbcdabbdda063;hmacsha1");
    mqtt_set_clean_session(client, 1);

    error = mqtt_connect(client);
    
    MQTT_LOG_D("mqtt connect error is %#0x", error);
    
    error = mqtt_subscribe(client, "$thing/down/property/S7271EG5D8/bdw01_led", QOS0, tos_topic_handler);
    
    MQTT_LOG_D("mqtt subscribe error is %#0x", error);
    
    while (1) {
        memset(&msg, 0, sizeof(msg));
        
        snprintf(report_buf, sizeof(report_buf), REPORT_DATA_TEMPLATE, lightness++);
        
        if (lightness > 100) {
            lightness = 0;
        }
       
        msg.qos = QOS0;
        msg.payload = (void *) report_buf;
        
        error = mqtt_publish(client, "$thing/up/property/S7271EG5D8/bdw01_led", &msg);
        
        MQTT_LOG_D("mqtt publish error is %#0x", error);
        
        tos_event_pend(&report_result_event, 
                       report_success|report_fail,
                       &match_flag,
                       TOS_TIME_FOREVER,
                       TOS_OPT_EVENT_PEND_ANY | TOS_OPT_EVENT_PEND_CLR);
        
        if (match_flag == report_success) {
            printf("report to Tencent IoT Explorer success\r\n");
        
        }else if (match_flag == report_fail){
            printf("report to Tencent IoT Explorer fail\r\n");
        }
        
        tos_task_delay(5000); 
    }
}

void application_entry(void *arg)
{
    mqttclient_task();
    while (1) {
        printf("This is a mqtt demo!\r\n");
        tos_task_delay(1000);
    }
}
