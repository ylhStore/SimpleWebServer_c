#include "webserverhandlerprocess.h"

//webServerHandlerProcess::webServerHandlerProcess()
//{

//}

REACTOR_ERROR_TYPE webServerHandlerProcess::CheackClientProcess(sockaddr_in* clnt_addr,int clntfd)
{
    return ERROR_TYPE_TEST_CONTINUE;
}

REACTOR_ERROR_TYPE webServerHandlerProcess::InputProcess(int clntfd)
{
    bzero(_buffer,sizeof(_buffer));
    //TODO Processing buffer
    int data_read = 0;
    int read_index = 0;
    int checked_index = 0;
    int start_line = 0;
    CHECK_STATE checkstate = CHECK_STATE_REQUESTLINE;
    while(1)
    {
        if((data_read = read(clntfd,_buffer+read_index,MAX_BUFFER_LENGTH - read_index)) < 0)
        {
            if(errno == ECONNRESET)
            {
                return ERROR_TYPE_ERROR;
            }
        }else if(data_read == 0){
            return ERROR_TYPE_FINISH;
        }
        printf("----------------recv buff--------------\n");
        printf("msg::\n %s \n",_buffer);
        printf("----------------recv buff over--------------\n");
        read_index += data_read;
        HTTP_CODE result = parse_content(_buffer,checked_index,checkstate,read_index,start_line);
        if(result == NO_REQUEST)
        {
            continue;
        }else if(result == GET_REQUEST)
        {
            //得到一个完整的，正确的http请求
            return ERROR_TYPE_FINISH;
        }else{
            //其他情况表示发生错误
            return ERROR_TYPE_FINISH;
        }

    }
    return ERROR_TYPE_TEST_CONTINUE;
}

REACTOR_ERROR_TYPE webServerHandlerProcess::OutputProcess(int clntfd)
{
    return ERROR_TYPE_TEST_CONTINUE;
}
REACTOR_ERROR_TYPE webServerHandlerProcess::HangupProcess(int clntfd)
{
    return ERROR_TYPE_TEST_CONTINUE;
}

//--------------------------------------------------------------------------------------------
LINE_STATUS webServerHandlerProcess::parse_line(char *bufffer, int &checked_index, int &read_index)
{
    char temp;
    for (;checked_index < read_index; ++ checked_index) {
        temp = bufffer[checked_index];
        if(temp == '\r')
        {
            if((checked_index + 1) == read_index)
            {
                return LINE_OPEN;
            }else if(bufffer[checked_index + 1] == '\n')
            {
                bufffer[checked_index++] = '\0';
                bufffer[checked_index++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }else if(temp == '\n')
        {
            if((checked_index > 1) && bufffer[checked_index - 1] == '\r')
            {
                bufffer[checked_index - 1] ='\0';
                bufffer[checked_index++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
    }
    return LINE_OPEN;
}

HTTP_CODE webServerHandlerProcess::parse_requestline(char *temp, CHECK_STATE &checkstate)
{
    char* url = strpbrk(temp," \t");
    if(!url)
    {
        return BAD_REQUEST;
    }
    *url++ = '\0';
    char* method = temp;
    if(strcasecmp(method,HTTP_GET) == 0)
    {
        printf("check method ok\n");
        printf("The request method is %s\n",HTTP_GET);
    }else{
        printf("The request method is %s\n",method);
        return BAD_REQUEST;
    }
    url += strspn(url," \t");
    char* version = strpbrk(url," \t");
    if(!version)
    {
        return BAD_REQUEST;
    }
    *version++ = '\0';
    version += strspn(version, " \t");
    //Only support http/1.1
    if(strcasecmp(version,SUPPORT_HTTP_VERSION) != 0)
    {
        return BAD_REQUEST;
    }
    if(strncasecmp(url,"http://",7) == 0)
    {
        url += 7;
        url = strchr(url,'/');
    }
    if(!url || url[0] != '/')
    {
        return BAD_REQUEST;
    }
    printf("The request URL is: %s\n",url);
    checkstate = CHECK_STATE_HEADER;
    return NO_REQUEST;
}

HTTP_CODE webServerHandlerProcess::parse_headers(char *temp)
{
    if(temp[0] == '\0')
    {
        return GET_REQUEST;
    }else if(strncasecmp(temp,"Host:",5) == 0)
    {
        temp += 5;
        temp += strspn(temp," \t");
        printf("the request host is: %s\n",temp);
    }else{
        printf("I can not handle this header\n");
    }
    return NO_REQUEST;
}

HTTP_CODE webServerHandlerProcess::parse_content(char *buffer, int &check_index, CHECK_STATE &checkstate, int &read_index, int &start_line)
{
    LINE_STATUS linestatus = LINE_OK;
    HTTP_CODE retcode = NO_REQUEST;
    while((linestatus = parse_line(buffer,check_index,read_index)) == LINE_OK)
    {
        char* temp = buffer + start_line;
        start_line = check_index;
        switch (checkstate) {
        case CHECK_STATE_REQUESTLINE:
        {
            retcode = parse_requestline(temp,checkstate);
            if(retcode == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }
            break;
        }
        case CHECK_STATE_HEADER:
        {
            retcode = parse_headers(temp);
            if(retcode == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }else if(retcode == GET_REQUEST)
            {
                return GET_REQUEST;
            }
            break;
        }
        default:{
            return INTERNAL_ERROR;
        }
        }
    }
    if(linestatus == LINE_OPEN)
    {
        return NO_REQUEST;
    }else{
        return BAD_REQUEST;
    }
}
















































