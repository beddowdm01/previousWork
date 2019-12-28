using System.Linq;
using System.Text;
using UnityEngine;

public class Test : MonoBehaviour
{
    [SerializeField]
    private string reverseString = "hello";

    [SerializeField]
    private string palindromeChecker = "racecar";

    [SerializeField]
    private string reverseSentence = "This is the sentence to reverse";

    [SerializeField]
    private string removeDuplicates = "This is the sentence to reverse";

    [SerializeField]
    private int[] intArray = { 1, 2, 3, 4, 5 };

    [SerializeField]
    private int checkPrime = 7;

    char[] charArray;

    void Start()
    {
        ReverseString();
        IsPalindrome();
        ReverseSentence();
        RemoveDuplicates();
        RotateArray();
        CheckPrime();
    }

    public void ReverseString()
    {
        charArray = reverseString.ToCharArray();

        for (int i = 0, x = charArray.Length - 1; i < x; i++, x--)
        {
            charArray[i] = reverseString[x];
            charArray[x] = reverseString[i];
        }
        Debug.Log(new string(charArray));
    }

    public void IsPalindrome()
    {
        bool isPalindrome = true;

        charArray = palindromeChecker.ToCharArray();

        for (int i = 0, x = charArray.Length - 1; i < x; i++, x--)
        {
            if (palindromeChecker[x] != palindromeChecker[i])
            {
                isPalindrome = false;
            }
        }
        if (isPalindrome)
        {
            Debug.Log("A palindrome");
        }
        else
        {
            Debug.Log("Not a palindrome");
        }
    }

    public void ReverseSentence()
    {
        StringBuilder reversedSentence = new StringBuilder();

        int counter = 0;
        int start = reverseSentence.Length - 1;
        int end = reverseSentence.Length - 1;

        while(start > 0)
        {
            if (reverseSentence[start] == ' ')
            {
                counter = start + 1;
                while (counter <= end)
                {
                    reversedSentence.Append(reverseSentence[counter]);
                    counter++;
                }
                reversedSentence.Append(' ');
                end = start - 1;
            }
            start--;
        }

        for (counter = 0; counter <= end; counter++)
        {
            reversedSentence.Append(reverseSentence[counter]);
        }
        Debug.Log(reversedSentence);
    }

    public void RemoveDuplicates()
    {
        string result = string.Empty;

        charArray = removeDuplicates.ToCharArray();

        for(int i = 0; i < removeDuplicates.Length; i++ )
        {
            if(!result.Contains(removeDuplicates[i]))
            {
                result += removeDuplicates[i];
            }
        }
        Debug.Log(result);
    }

    public void RotateArray()
    {
        int firstInt = intArray[0];
        for (int i = 0; i < intArray.Length - 1; i++)
        {
            intArray[i] = intArray[i + 1];
        }
        intArray[intArray.Length - 1] = firstInt;

        foreach(int i in intArray)
        {
            Debug.Log(i);
        }

    }

    public void CheckPrime()
    {
        bool isPrime = true;

        for(int i = 2; i < checkPrime; i++)
        {
            if ((checkPrime % i) == 0)
            {
                isPrime = false;
            }
        }
        Debug.Log("Is the number " + checkPrime + " prime? " + isPrime);
    }
}
