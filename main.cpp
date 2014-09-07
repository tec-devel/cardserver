#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include<uriparser/Uri.h>

#include "NetworkController.h"

#include "PlayerObject.h"
#include "TableObject.h"

#define PAGE "<html><head><title>libmicrohttpd demo</title>"\
             "</head><body>libmicrohttpd demo jerry</body></html>"

#define SOP_HEADER "Access-Control-Allow-Origin\0"

#include <iostream>
#include <sstream>

static std::vector<std::string> parseRestfulData(const char * url)
{
//    UriParserStateA state;
//    UriUriA uri;
//
//    state.uri = &uri;
//    if (uriParseUriA(&state, url) != URI_SUCCESS)
//    {
//        /* Failure */
//        uriFreeUriMembersA(&uri);
//    }
//
//    std::stringstream test(uri.pathHead->text.first);
//    std::string segment;
    std::vector<std::string> seglist;
//
//    while (std::getline(test, segment, '/'))
//    {
//        seglist.push_back(segment);
//    }
//
//    uriFreeUriMembersA(&uri);

    return seglist;
}

static int ahc_echo(void * cls,
                    struct MHD_Connection * connection,
                    const char * url,
                    const char * method,
                    const char * version,
                    const char * upload_data,
                    size_t * upload_data_size,
                    void ** ptr)
{
    static int dummy;
    const char * page = (const char*)cls;
    struct MHD_Response * response;
    int ret;

    if (strcmp(method, "GET") == 0)
    {
        if (&dummy != *ptr)
        {
            /* The first time only the headers are valid,
               do not respond in the first round... */
            *ptr = &dummy;
            return MHD_YES;
        }


        if (0 != *upload_data_size)
            return MHD_NO; /* upload data in a GET!? */
        *ptr = NULL; /* clear context pointer */

        response = MHD_create_response_from_data(strlen(page),
                                                 (void*) page,
                                                 MHD_NO,
                                                 MHD_NO);
        
        
        MHD_add_response_header(response, SOP_HEADER, "*\0");

        std::vector<std::string> seglist = parseRestfulData(url);

        if (!seglist.empty())
        {
            NetworkController::instance()->methodGet(seglist[0], seglist);
            ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        }
        else
        {
            ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        }


        MHD_destroy_response(response);
    }
    else if (strcmp(method, "POST") == 0)
    {
        if (&dummy != *ptr)
        {
            /* The first time only the headers are valid,
               do not respond in the first round... */
            *ptr = &dummy;
            return MHD_YES;
        }

        *ptr = NULL; /* clear context pointer */
        
        std::vector<std::string> restful_data = parseRestfulData(url);
        
        if(!restful_data.empty())
        {
            NetworkController::instance()->methodPost(restful_data[0], restful_data);
        }
        
        response = MHD_create_response_from_data(strlen(page), (void*) 0, MHD_NO, MHD_NO);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
    }
    else
        return MHD_NO; /* unexpected method */

    return ret;
}

int main(int argc,
         char ** argv)
{
    struct MHD_Daemon * d;
    if (argc != 2)
    {
        printf("%s PORT\n",
               argv[0]);
        return 1;
    }


    NetworkController::instance()->registerObject(new PlayerObject(std::string("player")));
    NetworkController::instance()->registerObject(new TableObject(std::string("table")));

    d = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
                         atoi(argv[1]),
                         NULL,
                         NULL,
                         &ahc_echo,
                         (void*)PAGE,
                         MHD_OPTION_END);

    if (d == NULL)
        return 1;
    (void) getchar();
    MHD_stop_daemon(d);
    return 0;
}
