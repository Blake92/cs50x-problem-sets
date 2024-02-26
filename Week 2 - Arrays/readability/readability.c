#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string);
int count_words(string);
int count_sent(string);

int main(void)
{
    string Text = get_string("Text: ");
    int letters = count_letters(Text);
    int words = count_words(Text);
    int sent = count_sent(Text);
    float L = ((float) letters / (float) words) * 100;
    float S = ((float) sent / (float) words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);      // using math.h function to average the grade
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}

int count_letters(string word)
{
    int count = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word [i] >= 65 && word [i] <= 90)
        {
            count ++;
        }
        else if (word [i] >= 97 && word [i] <= 122)
        {
            count ++;
        }
    }
    return count;
}

int count_words(string word)
{
    int count = 0;
    for (int i = 0; i < strlen(word) + 1; i++)      // the + 1 is to catch the NULL char after the last
    {
        if (word [i] == 32 || word [i] == '\0')
        {
            count ++;
        }
    }
    return count;
}

int count_sent(string word)
{
    int count = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        switch (word[i])          // switch condition with the index of ASCII chars . ? ! as cases
        {
            case 46:
                count++;
                break;
            case 33:
                count++;
                break;
            case 63:
                count++;
                break;
        }
    }
    return count;
}