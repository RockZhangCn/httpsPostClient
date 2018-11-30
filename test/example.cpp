#include "../httpspost/httpsPost.h"
#include <dlfcn.h>

void *handle = NULL;
/*
static void  loadLib(void) __attribute__((constructor));
static void  loadLib(void)
{
    printf("loadLib \n");
    handle = dlopen("libhttpspost_x86.so", RTLD_NOW);
}
*/

int main()
{
    string ip = "m.baidu.com";
    //string ip = "123.59.53.85";
    string buf;
    string url;
    string param;
    HttpsPost httpspost;
    
    int ok_couter = 0;
    int false_couter = 0;
    int connectCouter = 1;
    while(1)
    {
        // heartbeat
        url     = "https://m.baidu.com/";
        param   = "{\"chargeBoxSerialNumber\":{\"chargeBoxSerialNumber\":\"1012090561\"},\"chargePointSerialNumber\":{\"chargePointSerialNumber\":\"CSN00001\"}}";
        
        httpspost.State();
        //if(httpspost.State() == HTTPS_FREE)
        {
            do
            {
                int ret = httpspost.Connect(ip, 443, HOSTNAME_TYPE);
                //int ret = httpspost.Connect("m.baidu.com", 443, IP_TYPE);
                if( HTTPS_CONNECTED ==  ret)
                {
                    connectCouter++;
                    break;
                }
                else if( HTTPS_CONNECT_FALSE ==  ret)
                {
                    break;
                }
                
                // 防止死循环，设置超时或者尝试次数，close break
                
            }while(1);
        }

        if( HTTPS_SENTED == httpspost.Send(url, param) )
        {
            cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> send heartbeat" << endl;
            while(1)
            {
                int ret = httpspost.Recv(buf);
                if(HTTPS_RECVED == ret)
                {
                    ok_couter++;
                    //cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> revc heartbeat  " << endl;
                    //cout<< "response: " << endl << buf << endl;
                    break;
                }
                else if(HTTPS_RECV_FALSE == ret)
                {
                    false_couter++;
                    httpspost.Close();

                    //cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> recv heartbeat false and close" << endl;
                    break;
                }
            }
        }
        cout<<"connectCouter = "<< connectCouter << ", false_couter = " << false_couter << ", ok_couter = " << ok_couter << endl;
        sleep(65);
    }
}
