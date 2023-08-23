#include <SFML/Graphics.hpp>
#include<iostream>
#include"Windows.h"
#include <ctime>
#include <cstdlib>

using namespace std;
sf::RenderWindow window(sf::VideoMode(850, 850), "Josephus Game");  
sf::Sprite sprite;
sf::Sprite redcross;
sf::Texture texture;
sf::Texture textureforredcross;
template <typename t>
class queue
{
    int front;
    int rear;
    int size;
    t* arr;
    int count;        //to maintain start and end for our circular array
    int kill;    //the person to kill
public:
    queue();
    queue(int,int, int, t*, int,int);
    queue(const queue&);
    queue(int, int);
    ~queue();
    bool isempty();
    bool isfull();
    void enqueue(t);
    int dequeue(t&);
    void print();
    void traverseandkill(int, int);
    bool checkstatus();
};

template <typename t>
queue<t>::queue()
{
    front = 0;
    rear = 0;
    arr = nullptr;
    count = 0;
    size = 0;
    kill = 0;
}
template <typename t>
queue<t>::queue(int f, int r, int c, t* array, int s, int k)
{
    front = f;
    rear = r;
    count = c;
    size = s;
    arr = new t [size];
    kill = k;
}

template <typename t>
queue<t>::queue(const queue& obj)
{
    this->count = obj.count;
    this->size = obj.size;
    this->front = obj.front;
    this->rear = obj.rear;
    this->arr = new t[obj.size];
    for (int i = 0;i, size;i++)
    {
        this->arr[i] = obj.arr[i];
    }
    this->kill = obj.kill;
}


template <typename t>         //differently parameterised constructor
queue<t>::queue(int s, int k)
{
    this->size = s;
    this->kill = k;
    arr = new t[s];
    rear = 0;
    front = 0;
    this-> count = 0;
}

template <typename t>
queue<t>::~queue()
{
  
    delete arr;
    arr = nullptr;
}

template <typename t>
bool queue<t>::isempty()
{
    if (count == 0)
        return true;
    else
        return false;
}


template <typename t>
bool queue<t>::isfull()
{
    if (count == size )
        return true;
    else
        return false;
}



template <typename t>
void queue<t>::enqueue(t element)
{
    if (!isfull())
    {
        arr[rear] = element;
        rear++;
        count ++ ;
        if (count == size)
            rear = front;

    }
    else if (isfull())
    {
        count = size;
        rear = front;
    }

}

template <typename t>
int queue<t>::dequeue(t &element)
{
    if (!isempty())
    {
        if (count == size)
        {
            --rear;
        }
        if (rear <= -1)
            rear = size - 1;
        count--;
        element = arr[front];
        arr[front] = 'd';
        if (arr[front] == 'd')
        {
            int x = 50 + (100 * front);
            int y = 280;
            if (!textureforredcross.loadFromFile("cross.png"))
                return EXIT_FAILURE;
            redcross.setTexture(textureforredcross);
            redcross.setPosition(x, y);
            redcross.setScale(0.2, 0.2);

            window.draw(redcross);
            window.display();
            Sleep(1000);

        }
        while (arr[front] != 'a') 
        {
            front++;
            if (front >= size)
                front = 0;
        }

    }

    if (isempty())
    {
        rear = front;

    }
    
}


template <typename t>
void queue<t>::print()
{
    int x = 0;
    for (;x < size;++x)
    {
        cout << arr[x] << "   ";
    }
    cout << endl;
    cout << "the count is: " << count << endl;
}

template <typename t>
bool queue<t>::checkstatus()
{
    bool flag = false;
    for (int i = 0;i < size;i++)
    {
        if (arr[i] != 'd')
        {
            flag = true;
        }
    }
    return flag;          //true if there is somebody alive
}

template<typename t>
void queue<t>:: traverseandkill(int n,int k)     // function for game logic
{
    int player;
    srand((unsigned)time(0));
    do
    {
         player = 1 + (rand() % (n));      //to select a random player to start the game
    } while (player+1 >= n);
    cout << "game starts from player number: "<<player+1<< endl;
    front = player;
    char ele;
    int tokill=0;
    int increment = 1;
    tokill = player;
    while(count!=1)
    {

        for (int i = 0;i < k;i++)
        {
           
            tokill = tokill + increment;
            if (tokill == size)
            {
                tokill = 0;
            }
            while (arr[tokill] == 'd')
            {
                ++tokill;
                if (tokill == size)
                {
                    tokill = 0;
                }
            }
            
        }
        if (tokill == size)
        {
            tokill = 0;
        }
        while (arr[tokill] != 'a')
        {
            ++tokill;
            if (tokill == size)
            {
                tokill = 0;
            }
        }
        front = tokill;
        this->dequeue(ele);
        this->print();
        tokill = front ;  
        window.display();

      

    }
    cout << "player " << tokill + 1 << " is the winner" << endl;
    sf::Font font3;
    if (!font3.loadFromFile("newfont.ttf"))
    {
        cout << "error";
    }
    sf::Text text3;
    text3.setFont(font3);
    text3.setString("AND WE HAVE A WINNER!");
    text3.setCharacterSize(30);
    text3.setPosition(200, 400);
    text3.setFillColor(sf::Color(255, 255, 255));
    window.draw(text3);

}





int main()
{
    int players = 0, killing = 0;
    cout << "enter the number of players: ";
    cin >> players;
    cout << endl;
    cout << "enter the player number to kill: ";
    cin >> killing;
    cout << endl;
    queue<char>q1(players, killing);
 

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                           //---------------------------FRONT END---------------------------//
 
    if (!texture.loadFromFile("ninja.png"))  //
        return EXIT_FAILURE;  

    int x = 50;
    int y = 10;
    for (int i = 0;i < players;i++)
    {
        q1.enqueue('a');    //0 shows each player in the round
        sprite.setTexture(texture);   
        sprite.setPosition(sf::Vector2f(x, 290));
        sprite.setScale(sf::Vector2f(0.17, 0.17));
        x=x + 100;
    
        window.draw(sprite);

    }
    
    sf::Font font;
    if (!font.loadFromFile("newfont.ttf"))
    {
        cout << "error";
    }
    sf::Text text;
    text.setFont(font);
    text.setString("JOSEPHUS GAME");
    text.setCharacterSize(75);
    text.setPosition(100, 100);
    text.setFillColor(sf::Color(255, 255, 255));
    window.draw(text);


    sf::Font font2;
    if (!font2.loadFromFile("newfont.ttf"))
    {
        cout << "error";
    }
    sf::Text text2;
    text2.setFont(font);
    text2.setString("press enter key to start");
    text2.setCharacterSize(20);
    text2.setPosition(230, 210);
    text2.setFillColor(sf::Color(255, 0, 0));
    window.draw(text2);

  // Start the game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    q1.traverseandkill(players, killing);

                }
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    return 0;

                }
            }

        }
        // Draw the sprite
        window.display();
    }
}