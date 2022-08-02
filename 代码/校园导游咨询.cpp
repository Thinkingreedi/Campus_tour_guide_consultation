#include <iostream>
#include <cstring>
#include <iomanip>
#include <conio.h>
using namespace std;

#define Max 11    //矩阵阶数
#define MX 999999 //定义无穷大

int D[Max][Max]; //表示顶点到顶点的最短路径权值和的矩阵
int path[Max][Max]; //表示对于顶点的最小路径前驱矩阵

struct Users //账号密码
{
    char account[30];
    char password[30];
} use[50];
typedef struct Ver //顶点信息
{
    char num[4];        //顶点代号
    char name[41];      //顶点名称
    char instruct[401]; //顶点说明
} Ver;
typedef struct //邻接矩阵
{
    Ver vex[Max];       //顶点表
    int arcs[Max][Max]; //邻接矩阵
    int vexnum, arcnum; //图的当前顶点数和边数
} AMGragh;

int Login_System();                           //河南工业大学校园导游咨询系统登录系统
int Administrator_Login();                    //管理员登录界面
int Registered_Account();                     //管理员注册账号
int Login();                                  //管理员账号密码登录
void CreateUDG(AMGragh &G);                   //根据基本信息建图
int Administrators();                         //管理员功能(开放所有功能)
int User();                                   //用户功能(开放部分功能)
void Administrators_Menu();                   //管理员菜单界面
void User_Menu();                             //游客菜单界面
void Introduce();                             //河南工业大学简介
void Map();                                   //河南工业大学平面简图
void Query(AMGragh G);                        //查询景点基本信息
void All_Print(AMGragh G);                    //输出所有景点信息
void Modify_vertex(AMGragh &G);               //景点基本信息管理
void Modify_Edge(AMGragh &G);                 //路径基本信息管理
void Floyd(AMGragh G);                        //弗洛伊德算法获得两点最短路径
void Ask(AMGragh G);                          //用户咨询最短路径
void Path_Out(AMGragh G, int start, int end); //获得具体路径

int main(void) //主函数
{
    system("color F0"); //背景为黑，字体为亮白色
    Login_System();
    return 0;
}

int Login_System() //河南工业大学校园导游咨询系统登录系统
{
    int select;
    cout << "**********欢迎使用河南工业大学校园导游咨询系统**********" << endl;
    cout << "*                                                      *" << endl;
    cout << "*                   请选择登录方式                     *" << endl;
    cout << "*                                                      *" << endl;
    cout << "*     ★1.管理员登录   ★2.游客临时登录   ★3.退出     *" << endl;
    cout << "*                                                      *" << endl;
    cout << "********************************************************" << endl;
    cout << "请输入要选择的编号:" << endl;
    cin >> select;
    switch (select)
    {
    case 1:
        Administrator_Login();
        break;
    case 2:
        system("pause");
        system("cls");
        User();
        break;
    case 3:
        cout << "成功退出，欢迎下次使用..." << endl;
        system("pause");
        return 0;
        break;
    default:
        cout << "输入错误！没有该选项对应的操作！" << endl;
        break;
    }
    return 0;
}

int Administrator_Login() //管理员登录界面
{
    int select;
    while (select != 3)
    {
        system("cls");
        cout << "*********************管理员登录界面*********************" << endl;
        cout << "*                                                      *" << endl;
        cout << "*               ★1.账号密码直接登录                   *" << endl;
        cout << "*                                                      *" << endl;
        cout << "*               ★2.增添管理账号密码                   *" << endl;
        cout << "*                                                      *" << endl;
        cout << "*               ★3.退出                               *" << endl;
        cout << "*                                                      *" << endl;
        cout << "********************************************************" << endl;
        cout << "请输入要选择的编号:" << endl;
        cin >> select;
        switch (select)
        {
        case 1:
            Login();
            break;
        case 2:
            Registered_Account();
            break;
        case 3:
            cout << "成功退出，欢迎下次使用..." << endl;
            system("pause");
            return 0;
            break;
        default:
            cout << "输入错误！没有该选项对应的操作！" << endl;
            system("pause");
            break;
        }
    }
    return 0;
}

int Registered_Account() // 注册账号功能
{
    char account[30];
    char password[6], pd[6];
    int i, a = 0, flag = 0;

    cout << "注册帐号..." << endl;
    cout << "请输入用户账号和密码(账号、密码可以为数字,中文字母,英文字母,符号,密码必须6位)" << endl;
    cout << "请输入账号：" << endl;
    cin >> account;

    FILE *fp = fopen("Date.txt", "a+");
    while (!feof(fp))
    {
        fscanf(fp, "%s %sn", &use[a].account, &use[a].password);
        if ((strcmp(account, use[a].account) == 0))
        {
            cout << "注册失败,该账号已存在，请重新输入！" << endl;
            system("pause");
            flag = 1;
            fclose(fp);
            break;
        }
        a++;
    }

    if (flag == 1)
        return 0;

    strcpy(use[a].account, account);
    cout << "请你输入密码：" << endl;
    for (i = 0; i < 6; i++)
    {
        password[i] = _getch();
        cout << "*";
        use[a].password[i] = password[i];
        if (password[i] == '\r')
        {
            cout << "注册失败，请重新注册账号" << endl;
            return 0;
        }
    }
    cout << endl;
    cout << "再次确认密码：" << endl;
    for (i = 0; i < 6; i++)
    {
        pd[i] = _getch();
        cout << "*";
        if (use[a].password[i] != pd[i])
        {
            cout << "密码不对，请重新注册账号" << endl;
            return 0;
        }
    }
    fprintf(fp, "账号\t密码\n");
    fprintf(fp, "%s\t%s\n", use[a].account, use[a].password);
    printf("\n注册成功!!!\n");
    fclose(fp);
    system("pause");
    system("cls");
}

int Login() //登录账号功能
{
    char account[30];
    char ad[20], password;
    int i, j, a = 0;
    int flag = 0;

    cout << "**********************登录账号**********************" << endl;
    for (i = 0; i < 3; i++)
    {
        cout << "请输入帐号:" << endl;
        cin >> account;
        cout << "请输入密码:" << endl;
        for (j = 0; j < 6; j++)
        {
            password = _getch();
            cout << "*";
            ad[j] = password;
        }
        FILE *fp;
        fp = fopen("Date.txt", "r"); //读取文件操作
        while (!feof(fp))
        {
            fscanf(fp, "%s %sn", &use[a].account, &use[a].password);
            if ((strcmp(account, use[a].account) == 0) && (strcmp(ad, use[a].password) == 0))
            {
                flag = 1;
                fclose(fp);
                break;
            }
            a++;
        }
        cout << endl;
        if (flag == 1)
        {
            cout << "登录成功!" << endl;
            system("pause");
            system("cls");
            Administrators();
            break;
        }
        else
        {
            cout << "账号或者密码输入错误，你还有" << 2 - i << "次机会，请重新输入：" << endl;
        }
    }
    if (i == 3)
    {
        cout << "登录失败" << endl;
        system("pause");
        return 0;
    }
}

void CreateUDG(AMGragh &G) //根据基本信息建图
{
    G.vexnum = 10;
    strcpy(G.vex[0].num, "01");
    strcpy(G.vex[1].num, "02");
    strcpy(G.vex[2].num, "03");
    strcpy(G.vex[3].num, "04");
    strcpy(G.vex[4].num, "05");
    strcpy(G.vex[5].num, "06");
    strcpy(G.vex[6].num, "07");
    strcpy(G.vex[7].num, "08");
    strcpy(G.vex[8].num, "09");
    strcpy(G.vex[9].num, "10");
    strcpy(G.vex[0].name, "下沉广场");
    strcpy(G.vex[1].name, "图书馆");
    strcpy(G.vex[2].name, "4号教学楼");
    strcpy(G.vex[3].name, "莲 湖");
    strcpy(G.vex[4].name, "钟楼广场");
    strcpy(G.vex[5].name, "餐 厅");
    strcpy(G.vex[6].name, "学生宿舍");
    strcpy(G.vex[7].name, "操 场");
    strcpy(G.vex[8].name, "体育训练中心");
    strcpy(G.vex[9].name, "实验实训中心");
    strcpy(G.vex[0].instruct, "下沉广场是升国旗的场所，也会举办一些文艺晚会和校园招聘会，更是轮滑爱好者的乐园！");
    strcpy(G.vex[1].instruct, "图书馆环境安适，藏书丰富，配备现代化管理设施，是阅读书籍期末复习备战考研的绝佳场所！");
    strcpy(G.vex[2].instruct, "4号教学楼是、主要教学大楼，配备现代化教学设施，是老师上课和学生自习的场所，学习氛围浓厚!");
    strcpy(G.vex[3].instruct, "莲湖湖水清澈见底，这里能看到许多活泼的小鱼，还有几只抱团的鸭鸭！");
    strcpy(G.vex[4].instruct, "食堂包括第一、第二、第三食堂,里面的美食种类丰富，可以让你大饱口福!");
    strcpy(G.vex[5].instruct, "钟楼广场是平时社团举办活动的场所，经常会举办一些大型活动!");
    strcpy(G.vex[6].instruct, "学生宿舍为标准四/六人间，宿舍配备空调暖气，冬暖夏凉，空间充裕，居住舒适！");
    strcpy(G.vex[7].instruct, "操场包括网球场，篮球场，足球场等，你可以在田径场挥洒汗水，晚上可能会举办音乐会哦！");
    strcpy(G.vex[8].instruct, "体育馆设施齐全，包括乒乓球场，羽毛球场，攀岩场地等，快来和大家一起运动吧！");
    strcpy(G.vex[9].instruct, "实验实训中心提供场地和设施让学生进行物理、生物实验和金工、电子工艺实习！");
    G.arcs[1][2] = G.arcs[2][1] = 8;
    G.arcs[1][3] = G.arcs[3][1] = 3;
    G.arcs[2][5] = G.arcs[5][2] = 17;
    G.arcs[2][4] = G.arcs[4][2] = 4;
    G.arcs[2][10] = G.arcs[10][2] = 31;
    G.arcs[3][6] = G.arcs[6][3] = 21;
    G.arcs[4][5] = G.arcs[5][4] = 12;
    G.arcs[5][6] = G.arcs[6][5] = 6;
    G.arcs[5][7] = G.arcs[7][5] = 5;
    G.arcs[5][9] = G.arcs[5][9] = 27;
    G.arcs[7][8] = G.arcs[8][7] = 21;
    G.arcs[8][9] = G.arcs[9][8] = 13;
    G.arcs[9][10] = G.arcs[10][9] = 18;
    for (int i = 1; i <= 10; i++) //初始化路径长度
        for (int j = 1; j <= 10; j++)
        {
            if (G.arcs[i][j] == 0 && i != j)
                G.arcs[i][j] = MX;
        }
    G.arcnum = 13;        
}

int Administrators() //管理员功能(开放所有功能)
{
    AMGragh G;
    memset(G.arcs, 0, sizeof(G.arcs));
    CreateUDG(G);
    int m;
    while (m != 8)
    {
        Administrators_Menu();
        cin >> m;
        switch (m)
        {
        case 1:
            Introduce();
            break;
        case 2:
            Map();
            break;
        case 3:
            Query(G);
            break;
        case 4:
            All_Print(G);
            break;
        case 5:
            Ask(G);
            break;
        case 6:
            Modify_vertex(G);
            break;
        case 7:
            Modify_Edge(G);
            break;
        case 8:
            cout << "感谢您的使用！" << endl;
            return 0;
        default:
            cout << "没有该选项！" << endl;
        }
        system("pause");
        system("cls");
    }
    return 0;
}

int User() //用户功能(开放部分功能)
{
    AMGragh G;
    memset(G.arcs, 0, sizeof(G.arcs));
    CreateUDG(G);
    int m;
    while (m != 5)
    {
        User_Menu();
        cin >> m;
        switch (m)
        {
        case 1:
            Introduce();
            break;
        case 2:
            Map();
            break;
        case 3:
            Query(G);
            break;
        case 4:
            Ask(G);
            break;
        case 5:
            cout << "感谢您的使用！" << endl;
            return 0;
        default:
            cout << "没有该选项！" << endl;
        }
        system("pause");
        system("cls");
    }
    return 0;
}

void Administrators_Menu() //管理员菜单界面
{
    cout << "***************欢迎您**************" << endl;
    cout << "*       ★1、查看校园详细信息     *" << endl;
    cout << "*       ★2、查看该校园平面图     *" << endl;
    cout << "*       ★3、校园景点信息查询     *" << endl;
    cout << "*       ★4、输出所有景点信息     *" << endl;
    cout << "*       ★5、景点最短路径查询     *" << endl;
    cout << "*       ★6、修改景点基本信息     *" << endl;
    cout << "*       ★7、修改路径基本信息     *" << endl;
    cout << "*       ★8、 返回上一级菜单      *" << endl;
    cout << "***********************************" << endl;
    cout << "请选择..." << endl;
}

void User_Menu() //用户菜单界面
{
    cout << "***************欢迎您**************" << endl;
    cout << "*       ★1、查看校园详细信息     *" << endl;
    cout << "*       ★2、查看该校园平面图     *" << endl;
    cout << "*       ★3、校园景点信息查询     *" << endl;
    cout << "*       ★4、景点最短路径查询     *" << endl;
    cout << "*       ★5、退出                 *" << endl;
    cout << "***********************************" << endl;
    cout << "请选择..." << endl;
}

void Introduce() //河南工业大学简介
{
    cout << endl;

    cout << "河南工业大学（Henan University of Technology）位于河南省会郑州市，是河南省人民政府和国家粮食局共建高校;始建于1956年，先后隶属国家粮食部、商业部和国内贸易部；1959年开展本科教育，1981年开始硕士研究生教育，2013年开始博士研究生教育，2017年获批硕士研究生推免资格，2018年获批博士学位授予单位； 1998年划归河南省管理，河南省人民政府和国家粮食局于2010年签约共建河南工业大学。" << endl;

    cout << "建校至今，学校坚持“扎根中原，立足行业，服务全国，面向世界”的办学定位，严守“育人为本、质量立校、特色发展”的办学理念，秉承“明德、求是、拓新、笃行”的校训，大力弘扬“崇尚科学、勇于探索、报国兴学、自强不息”的工大精神，凝练形成了“团结进取，务实高效”的校风、“博学奉献”的教风和“勤奋诚信”的学风。" << endl;

    cout << "经过历代工大人的励精图治和薪火传承，学校已经发展成为一所以工学为主，涵盖理学、经济学、管理学、法学、文学、艺术学和农学等学科协调发展的多科性大学，不仅具备完整的学士、硕士、博士三级人才培养体系，而且作为第二单位成功入选国家首批“ 2011协同创新计划”，是教育部“中西部高校基础能力建设工程”和“卓越工程师教育培养计划”建设高校，在推动行业、区域和国家经济社会发展，实现教育振兴的过程中做出了应有贡献，在人才培养、科学研究、社会服务等方面均取得了优异成绩。 " << endl;

    cout << endl;
}

void Map() //河南工业大学平面简图
{
    cout << " ————————————————————————————" << endl;
    cout << "|                   河南工业大学平面图                  |" << endl;
    cout << " ————————————————————————————" << endl;
    cout << "|                           北门                        |" << endl;
    cout << "|           [8]操场————————[7]宿舍              |" << endl;
    cout << "|            |                      |                   |" << endl;
    cout << "|            |                      |                   |" << endl;
    cout << "|            |—————————[5]钟楼广场——         |" << endl;
    cout << "|            |                  |      |       |        |" << endl;
    cout << "|          [9]体育中心          |      |     [6]餐厅    |" << endl;
    cout << "|西门       |                   |      |       |    东门|" << endl;
    cout << "|           |             [4]莲湖      |       |        |" << endl;
    cout << "|           |                 |        |       |        |" << endl;
    cout << "|           |               [2]图书馆—        |        |" << endl;
    cout << "|   [10]基础实训中心 —————|               |        |" << endl;
    cout << "|        北                    |———[3]4号教学楼      |" << endl;
    cout << "|        ↑                    |                        |" << endl;
    cout << "|  西 ← — →东             [1]下沉广场                |" << endl;
    cout << "|        ↓                                             |" << endl;
    cout << "|        南                  南门                       |" << endl;
    cout << " ————————————————————————————" << endl;
}

void Query(AMGragh G) //查询景点基本信息
{
    cout << "请输入查询景点的代号(例如 06)：";
    char c[5];
    cin >> c;
    int i;
    for (i = 0; i < G.vexnum; i++) // n较小，采用顺序查找即可
    {
        if (strcmp(c, G.vex[i].num) == 0)
        {
            cout << "代号：" << G.vex[i].num << endl;
            cout << "景点名称:" << G.vex[i].name << endl;
            cout << "简介：" << G.vex[i].instruct << endl;
            break;
        }
    }
    if (i == G.vexnum)
    {
        cout << "该代号不存在!" << endl;
    }
}

void All_Print(AMGragh G) //输出所有景点信息
{
    cout << "----------------------------------河南工业大学景点信息----------------------------------" << endl;
    cout << setw(16) << setiosflags(ios::left) << "景点名称"
         << setw(8) << setiosflags(ios::left) << "代号"
         << setw(16) << setiosflags(ios::left) << "简介" << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        cout << setw(16) << G.vex[i].name << setw(8) << G.vex[i].num << setw(60) << G.vex[i].instruct << endl;
    }
    cout << endl;
}

void Modify_vertex(AMGragh &G) //景点基本信息管理
{
    All_Print(G);
    int flag = 0;
    cout << "请输入要修改信息的代号(例如 06)：";
    char c[5];
    cin >> c;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (strcmp(c, G.vex[i].num) == 0) //字符串比较的方法进行查找
        {
            flag = 1;
            memset(G.vex[i].name, 0, sizeof(G.vex[i].name)); //把G.vex[i].**中所有字节换做字符“0”，对字符串的初始化
            memset(G.vex[i].instruct, 0, sizeof(G.vex[i].instruct));
            char name1[41];
            char instruct1[401];
            cout << "请输入修改后的景点信息：" << endl;
            cout << "景点名称：";
            cin >> name1;
            cout << "简介：";
            cin >> instruct1;
            strcpy(G.vex[i].name, name1); //字符串拷贝函数
            strcpy(G.vex[i].instruct, instruct1);
            cout << "修改成功！" << endl;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "输入错误！" << endl;
    }
}

void Modify_Edge(AMGragh &G) //路径基本信息管理
{
    Map();
    int i, j, k;
    cout << "请输入待修改的边(例如5 8):" << endl;
    cin >> i >> j;
    if ((G.arcs[i][j] != MX && G.arcs[j][i] != MX) && (i >= 1 && i <= 10) && (j >= 1 && j <= 10))
    {
        cout << "请输入修改后的边长(例如 6)：";
        cin >> k;
        G.arcs[i][j] = G.arcs[j][i] = k;
        cout << "修改成功！" << endl;
    }
    else
    {
        cout << "输入错误！" << endl;
    }
}

void Ask(AMGragh G) //用户咨询最短路径
{
    Map();
    cout << "请输入起点和目的地(例如06 08):";
    int i, j;
    cin >> i >> j;
    if ((i >= 1 && i <= 10) && (j >= 1 && j <= 10))
    {
        Floyd(G);
        cout << endl
             << endl
             << "从" << G.vex[i - 1].name << "到" << G.vex[j - 1].name << ":" << endl
             << endl
             << "最短路径长度：" << D[i][j] * 10 << "米" << endl; //存的路径为缩小10倍的距离，按比例尺还原
        cout << endl;
        Path_Out(G, i, j);
    }
    else
    {
        cout << "输入错误！" << endl;
    }
    cout << endl;
}

void Floyd(AMGragh G) //弗洛伊德算法，获得两点最短路径
{
    int i, j, k;
    for (i = 1; i <= G.vexnum; ++i) //初始化
        for (j = 1; j <= G.vexnum; j++)
        {
            D[i][j] = G.arcs[i][j];
            if (D[i][j] < MX && i != j)
                path[i][j] = i;
            else
                path[i][j] = -1;
        }
    for (k = 1; k <= G.vexnum; k++) //更新最短路径
        for (i = 1; i <= G.vexnum; ++i)
            for (j = 1; j <= G.vexnum; j++)
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = path[k][j];
                }
}

void Path_Out(AMGragh G, int start, int end) //获得具体路径
{
    int p[Max];
    p[0] = end;
    int i = 1;
    while (start != end)
    {
        end = path[start][end];
        p[i] = end;
        ++i;
    }
    cout << "路径:" << G.vex[start - 1].name;
    i = i - 2;
    while (i >= 0)
    {
        cout << "→" << G.vex[p[i] - 1].name;
        --i;
    }
    cout << endl;
}
