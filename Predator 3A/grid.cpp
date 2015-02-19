#include "grid.h"

Grid::Grid()
{
    grid = new Creature**[size];
    for(int i = 0; i < size; i++)
    {
       grid[i] = new Creature*[size];
       for(int j = 0; j < size; j++)
       {
           grid[i][j] = NULL;
       }
    }
}

Grid::~Grid()
{
    for(int i = 0; i < size; i++)
       {
           for(int j = 0; j < size; j++)
           {
               delete grid[i][j];
               grid[i][j] = NULL;
           }
       }
}

void Grid::Display()
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(grid[i][j] == NULL)
                cout << "- ";
            else
            {
                if(grid[i][j]->Face() == 'H')
                    cout << 'H' << " ";
                else if(grid[i][j]->Face() == 'P')
                    cout << 'P' << " ";
                else if(grid[i][j]->Face() == 'D')
                    cout << 'D' << " ";
                else if(grid[i][j]->Face() == 'V')
                    cout << 'V' << " ";
            }
        }
        cout << endl;
    }
}

void Grid::InitializeH()
{
     int count=0;
     while(count<20)
     {
         int X = rand()%size;
         int Y = rand()%size;
         if(grid[X][Y] == NULL)
         {
             grid[X][Y] = new Human;
             count++;
         }
     }
}

void Grid::InitializeP()
{
    int count=0;
    while(count<100)
    {
        int X = rand()%size;
        int Y = rand()%size;
        if(grid[X][Y] == NULL)
        {
            grid[X][Y] = new Prey;
            count++;
        }
    }
}

void Grid::InitializeD()
{
    int count=0;
    while(count<1)
    {
        int X = rand()%size;
        int Y = rand()%size;
        if(grid[X][Y] == NULL)
        {
            grid[X][Y] = new Dragon;
            count++;
        }
    }
}

void Grid::InitializeV()
{
    int count=0;
    while(count<5)
    {
        int X = rand()%size;
        int Y = rand()%size;
        if(grid[X][Y] == NULL)
        {
            grid[X][Y] = new Vampire;
            count++;
        }
    }
}

void Grid::Set(int x, int y, Creature* SetThis)
{
    grid[x][y] = SetThis;
}

void Grid::Run()
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(grid[i][j] != NULL &&(grid[i][j]->Finished() == false))
            {
                grid[i][j]->Move(i,j,grid);
            }
        }
    }
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(grid[i][j] != NULL &&(grid[i][j]->Finished() == true))
            {
                grid[i][j]->Breed(i,j,grid);
            }
        }
    }
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->Finish = false;
            }
        }
    }
}

Creature* Grid::Getthis(int x, int y)
{
    return grid[x][y];
}

void Grid::Save()
{
    ofstream fout;
    fout.open("prtscr.txt");
    if (fout.fail( ))
    {
        cout << "Output file opening failed.\n";
        exit(1);
    }
    for(int i = 0 ; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(grid[i][j] == NULL)
                fout << '-';
            else
                fout << grid[i][j]->Face();
            fout << " ";
        }
        fout << endl;
    }
    fout.close();
}

void Grid::Load()
{
    {
        ifstream fin;
        fin.open("prtscr.txt");
        if (fin.fail( ))
        {
            cout << "Input file opening failed.\n";
            exit(1);
        }
        char next;
        int x = 0;
        int y = 0;
        while(! fin.eof())
        {
            fin.get(next);
            switch(next)
            {
            case '-':
                    grid[x][y] = NULL;
                    y++;
                    break;
            case 'H':
                    grid[x][y] = new Human;
                    y++;
                    break;
            case 'P':
                    grid[x][y] = new Prey;
                    y++;
                    break;
            case 'D':
                    grid[x][y] = new Dragon;
                    y++;
                    break;
            case '\n':
                    x++;
                    y = 0;
                    break;
            }
        }
        fin.close();
    }
}

void Grid::SunRise()
{

}
