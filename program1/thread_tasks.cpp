#include <iostream>
#include <algorithm>
#include <thread>
#include <mutex>
#include <string.h>



/*custom headers*/

#include "../headers/tools/bsd.h"
#include "../headers/tasks/thread_tasks.h"


using namespace std;


/* checks if every single char is digit */
bool is_digits(string &str)
{
    return all_of(str.begin(), str.end(), ::isdigit);
}


int countdigit(int n)
{
    if (n/10 == 0)
        return 1;
    return 1 + countdigit(n / 10);
}

/* descending sort of string */
string desc_sort(string &text)
{

  for (int i = 0; i < (text.length()) - 1; i++)
  {
    if (text.at(i) < text.at(i + 1))
    {
      char temp = text.at(i + 1);
      text.at(i + 1) = text.at(i);
      text.at(i) = temp;
      i = -1;
    }
  }

  return text;
}


/* replaces the even digits of the only numeric string with
 the string passed through paramters*/

bool is_char_even(char ch){

    return isdigit(static_cast<unsigned char>(ch)) && ((ch - '0') % 2) == 0;
}

void replace_even_with_string(string &input,const string replacing_str){

    for(int i =0; i< input.length(); i++ ){

        if(is_char_even(input.at(i))){
            input.replace(i, 1, replacing_str.data());
        }
    }
}

/* function to get sum of all digits in string */
int sum_of_digits(string str){

    int sum = 0;
    for (int i=0; i<str.length(); ++i)
    {

        if (isdigit(str.at(i))){

            /* convert charater to int (ASCII - 48)  */
            int a = int(str.at(i) - '0');

            sum = sum + a;
        }
    }
    return sum;
}

/******************************************************************************/
/* first thread task  */

void thread_tasks::thread1_task(){

    while(1){
        

        /*locking the threads to avoid race conditions*/
        unique_lock<mutex> lock(mtx);

        {
            string input_digits;
            bool correct_input = false;
            
            /*getting user input and checking for conditions*/

            cout << "Type some numbers please : ";
            while (!correct_input)
            {
                getline (cin, input_digits);

                if(!is_digits(input_digits))
                {
                    cout << "[-] your input wasn't digits only, Please try again: ";
                }else if(input_digits.length() > 64){
                    cout << "[-] The length of input exceeds the 64 digits,\nPlease try something shorter: ";
                }
                else{
                    correct_input = true;
                }
            }

            /* sorting the numbers in the string */
            desc_sort(input_digits);

            /* replace the even numbers with letters 'KB' */
            replace_even_with_string(input_digits, "KB");

            /*alocate memory for buffer and pass the valid user input into it*/
            buffer = new char[input_digits.length() + 1];

            copy(input_digits.begin(), input_digits.end(),
                buffer);
            buffer[input_digits.length() + 1] = '\0';

            ready_to_read = true;                   

        }

        lock.unlock();

        /*10 miliseconds of sleep after finishing and
         unlocking just for extra safety*/
        this_thread::sleep_for(chrono::microseconds(10));
    }
}

/******************************************************************************/

/* second thread task*/
void thread_tasks::thread2_task(){

    while(1){

        unique_lock<mutex> lock(mtx);
        
        {
            /*extra  checking  for extra safety it's not needed
            (doesn't cost performance)*/
            if(buffer && ready_to_read){
                
                cout << buffer << '\n';
                ready_to_read = false;


                int sum = sum_of_digits(buffer);

                cout << "the sum : " << sum <<'\n';

                /*serializing the sum into a buffer to send it via tcp bsd sockets*/

                char *ser_buffer = new char[countdigit(sum)];

                sprintf(ser_buffer, "%d", sum);


                bsd_sender sender;
                sender.send_data(ser_buffer);

            }
        }
        lock.unlock();
        this_thread::sleep_for(chrono::microseconds(10));
    }
}

/******************************************************************************/
