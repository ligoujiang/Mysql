#include <mysql/mysql.h>
#include <iostream>
int main(){
    MYSQL mysql; //实例化mysql句柄
    mysql_init(&mysql);//初始化句柄
    if(mysql_real_connect(&mysql,"127.0.0.1","root","123456","db_test",3306,NULL,0)==NULL){
        std::cout<<"连接失败！错误原因："<<mysql_error(&mysql)<<std::endl;
        return -1;
    };

    mysql_query(&mysql,"select * from tb_user");

    MYSQL_RES* res; //返回结果集
    res=mysql_store_result(&mysql);

    MYSQL_ROW row;
    while(row=mysql_fetch_row(res)){
        std::cout<<row[0]<<std::endl;
    }   
    return 0;
}