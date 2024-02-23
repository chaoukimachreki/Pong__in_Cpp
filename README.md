# Pong__in_Cpp
a variation of the pong Game  in C++ 

I) There are two main challenges in getting this code to compile - of course i am supposing that you are a complete beginner , i don't see how jonathan Blow would be interested in checking the code to this game - 

1 - visual studio community edition : make sure to download the vs community edition with the game development packages, you'll be prompted to choose your download type. you wont miss it , at the time of writing the whole thing is about 2.4 gb.

2- clone the repo ,  you'll see two .cpp files, one header file and the libraries zip file called External- extract it.

2.1 Start a new project and add the found .cpp and .h files to the source files located in the explorer pane.

2.2 now the tricky part is linking your project to the SDL , SOIL and GLEW libraries. for this check this link: 
https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php. 



press the green triangle up to build the game !  

II) the Game itself is simple :
- how do you create movement ? the ball's position should be a function of time;  it's like walking without brains , instead of the brain deciding to make a step  , you tell your feet make a step every scond or .start a stop watch and you'll see that in 5 seconds youll have made 5 steps. now in which direction is that ?? it's like those cars that you turn on and let it run and then pick up with your hand when it hits the wall to put it in a different direction. you set the direction whether it's straight to the wall or tilted to the room corner. and this is made through a velocity variable of course through x and y coordinates.
    
- when the ball hits the upper, lower wall or the paddle the x coordinate inverts ! the y inversts for the side walls ! 
_____________________________________________________________________________________________________________________________________________________________________________________
                                                  /|\
                                                /  |  \
                                              /    |   \
                                            /      |      \ 
                                          /        |        \
                                    O (-x,y)<----->|<----> O (x,y)
                                            same y | same y
                                                   |  
                                                   |
                               (-x) ---------------|------------------
                                                   | 
                                                   |
                                                   |
                                                   | (y) 
