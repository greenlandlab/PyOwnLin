#include <iostream>
#include <string.h>
#include <sstream>



std::string arg_array[50] = { "-out=ASM", "-o", "-Include", "-IncUnLib" , "-IncUnLibF", "-src", "-MultiInc"}; // all arguments
std::string arg_s_array[3] = { "-src", "-Include", "-o" }; // args requiring parameters

std::string out = "a.out"; // output file name by default a.out
std::string src; // The source file

int arg_exists(std::string arg); // check if a argument exists
int special_arg(std::string arg); // check if a arg is special (args which next val is a parameter)

template<typename...  ARGS>
void error(std::string msg,int argc, ARGS... arg);


int main(int argc, char const *argv[]) // entrypoint
{
    if (argc < 3 ) // compiler need minimum 2 args ( -src then the path )
    {
        error("PyownLin Fatal Command Line error: not enough arguments", NULL); // errror and exit
    }

    for (size_t i = 1; i < argc; i++) // check if all args actually exist
    {
        if ( arg_exists(argv[i]) )
        {
            continue;
        }
        else if ( special_arg(argv[i-1]) )
        {
            continue;
        }
        
        else
        {
            error("PyownLin Fatal Command line error: the argument ", 2, argv[i], " doesn't exist");
        }
        
        
    }
    
    bool src_exist;

    for (size_t i = 1; i < argc; i++) // check if some args exist
    {
        if ( strcmp(argv[i], "-src" ) ) // if src exists
        {
            src_exist = true;
        }
        else
        {
            continue;
        }
        
        
    }

    if ( !src_exist == true ) 
    {
        error("PyownLin Fatal Command Line Error: no -src file resulting in no file to compile", 0);
    }
    
    
    
}

int arg_exists(std::string arg)
{
    
    for (size_t i = 0; i < 50; i++) // loop through the avaliable args array and see if the arg exists if not the next line will return 1 
    {
        if (strcmp(arg_array[i].c_str(), arg.c_str()) == 0) // compare the current argument to the provided one (current = arg[i]) and need .c_str bc strcmp doesnt support std::string
        {
            return 0;
        }
        else // if not continue
        {
            continue;
        }
        
        
    }
    
    

    return 1; // not found results in error
}

int special_arg(std::string arg)
{
    for (size_t i = 0; i < 3; i++)
    {
        if ( strcmp(arg.c_str(), arg_s_array[i].c_str()) == 0 ) // match found special arg = true
        {
            return 0;
        }
        
    }
    
    return 1; // no special arg );
}

template <typename... ARGS>
void error(std::string msg, int argc, ARGS... arg)
{

    std::ostringstream oss;

    oss << msg;
    ((oss << " " << arg), ...);
    std::cerr << oss.str() << std::endl;

    exit(1);

}
