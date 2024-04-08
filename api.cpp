#include <mysql/mysql.h>
#include <iostream>
int main(){
    //实例化和初始化mysql句柄
    MYSQL mysql; //实例化mysql句柄
    mysql_init(&mysql);//初始化句柄
    if(mysql_real_connect(&mysql,"127.0.0.1","root","123456","db_test",3306,NULL,0)==NULL){
        std::cout<<"连接失败！错误原因："<<mysql_error(&mysql)<<std::endl;
        return -1;
    };

    //查询数据
    if(mysql_query(&mysql,"select * from tb_user")!=0){
        std::cout<<"查询失败！错误原因："<<mysql_error(&mysql)<<std::endl;
        return -1;
    };

    //获取数据
    MYSQL_RES* res; //创建结果集，用来保存获取到的数据库数据
    res=mysql_store_result(&mysql); //获取数据
    if(res==NULL){
        std::cout<<"返回结果集失败！错误原因："<<mysql_error(&mysql)<<std::endl;
        return -1;
    }

    //获取结果集中字段的个数
    int num=mysql_num_fields(res);
    std::cout<<"当前结果集的字段个数为："<<num<<std::endl;

    //获取结果集中的表头（字段名）
    MYSQL_FIELD* fields=mysql_fetch_field(res); //得到存储头信息的数组的地址
    num=mysql_num_fields(res);  //得到列数
    //遍历字段名
    for(int i=0;i<num;i++){
        std::cout<<"当前结果集的表头为："<<fields[i].name<<std::endl;
    }

    //遍历获取的结果集
    MYSQL_ROW row;
    while(row=mysql_fetch_row(res)){
        for(int i=0;i<num;i++){
            std::cout<<row[i]<<" ";
        }
        std::cout<<std::endl;
    }

    //事务
    //设置事务
    mysql_autocommit(&mysql,0); //0为手动，1为自动
    mysql_query(&mysql,"insert into tb_user values(3,'pxy',18)");
    int temp=0;
    std::cin>>temp;
    if(temp==0){
        mysql_rollback(&mysql); //事务回滚
    }else{
        mysql_commit(&mysql);//事务提交
    }
    //资源回收
    mysql_free_result(res); //释放结果集
    mysql_close(&mysql);   //释放句柄
    return 0;
}