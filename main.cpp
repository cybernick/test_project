#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <shapelib-1.3.0/shapefil.h>

using namespace std;

char chr_menu;
struct point
{
    double x;
    double y;
};

vector< vector<point> > lines;

void save_in_shp_file(string path, int SHPT)
{
    SHPHandle hSHP;
    hSHP=SHPCreate(path.c_str(),SHPT);
    for (int i = 0; i < lines.size(); i++)
    {
        int vertices = lines.at(i).size();
        double padfX[vertices];
        double padfY[vertices];
        for (int j = 0; j < lines.at(i).size(); j++)
        {
            padfX[j] = lines[i][j].x;
        }
        for (int j = 0; j < lines.at(i).size(); j++)
        {
            padfY[j] = lines[i][j].y;
        }

        SHPObject* Object;
        Object=SHPCreateSimpleObject(SHPT, vertices, padfX, padfY, NULL);
        SHPWriteObject(hSHP,-1,Object);

    }
    SHPClose(hSHP);
}

void read_from_shp(string path)
{
    SHPHandle hSHP;
    int pnEntities=0;
    hSHP=SHPOpen(path.c_str(), "rb+");
    SHPGetInfo(hSHP, &pnEntities, NULL, NULL, NULL);
    lines.clear();
    for (int i = 0; i < pnEntities; i++)
    {
        SHPObject* Object;
        Object=SHPReadObject(hSHP, i);
        double arr_x[Object->nVertices];
        double arr_y[Object->nVertices];
        for (int i = 0; i < Object->nVertices; i++)
        {
            arr_x[i] = Object->padfX[i];
            arr_y[i] = Object->padfY[i];
        }
        vector<point> line;
        for (int i = 0; i < Object->nVertices; i++)
        {
            point p;
            p.x = arr_x[i];
            p.y = arr_y[i];
            line.push_back(p);
        }
        lines.push_back(line);
        line.clear();
    }
}

void menu()
{
    cout<<"Для сохранения в файл нажмите S, для считывания из файла нажмите R, для вывода на консоль вектора W"<<endl;
    cout<<"для выхода нажмите E."<<endl;
    cin>>chr_menu;
    return;
}

int main()
{
    cout<<"Добро пожаловать в приложение по работе с shapefile!"<<endl;
    cout<<"Производиться инициализация вектора линий..."<<endl;

    for (int i = 0; i < 10; i++)
    {
        vector<point> line;
        for (int j = 0; j < 2+i; j++)
        {
            point p;
            p.x = j;
            p.y = j;
            line.push_back(p);
        }
        lines.push_back(line);
        line.clear();
    }

    cout<<"Вектор инициализирован..."<<endl;
    cout<<"                         "<<endl;
    cout<<"Для сохранения в файл нажмите S, для считывания из файла нажмите R,";
    cout<<"для вывода на консоль вектора W, для выхода нажмите E."<<endl;
    cin>>chr_menu;
    while (chr_menu != 'E' && chr_menu != 'e')
    {
        if (chr_menu == 'S' || chr_menu == 's')
        {
            string  polyline_path;
            string  multi_point_path;
            cout<<"Введите путь и имя создаваемого файла для полилайнов";
            cout<<"(например: /home/username/polyline.shp)"<<endl;
            getline (cin, polyline_path);
            getline (cin, polyline_path);

            cout<<"Введите путь и имя создаваемого файла для мультиточек";
            cout<<"(например: /home/username/polyline.shp)"<<endl;
            getline (cin, multi_point_path);

            save_in_shp_file(polyline_path,SHPT_ARC);
            save_in_shp_file(multi_point_path,SHPT_MULTIPOINT);
        }
        else if (chr_menu == 'R' || chr_menu == 'r')
        {
            string  path;
            cout<<"Введите путь и имя файла для чтения файлов полилайнов или мультиточек";
            cout<<"(например: /home/username/polyline.shp)"<<endl;
            getline (cin,path);
            getline (cin,path);

            read_from_shp(path);
        }
        else if (chr_menu == 'W' || chr_menu == 'w')
        {
            for (int i = 0; i < lines.size(); i++)
            {
                cout<<"Линия номер-"<<i<<endl;
                for (int j = 0; j < lines.at(i).size(); j++)
                {
                    cout<<"x-"<<j<<":"<<lines.at(i).at(j).x<<" "<<"y-"<<j<<":"<<lines.at(i).at(j).y<<endl;
                }
            }
        }
        menu();
    }

    return 0;
}

