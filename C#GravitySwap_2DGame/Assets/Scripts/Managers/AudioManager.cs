/*A class to handle all audio within the game*/
using UnityEngine.Audio;
using System;
using UnityEngine;

public class AudioManager : MonoBehaviour
{

    public Sound[] sounds; //creates an array of Sounds

    public static AudioManager Instance;

    // Start is called before the first frame update
    void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        else
        {
            Destroy(gameObject);
            return;
        }


        DontDestroyOnLoad(gameObject);//allows it to persist through levels

        foreach (Sound s in sounds)//loops through the sound array
        {
            s.source = gameObject.AddComponent<AudioSource>();
            s.source.clip = s.clip;

            s.source.volume = s.volume;
            s.source.spatialBlend = s.spatialblend;
            s.source.pitch = s.pitch;
            s.source.loop = s.loop;
        }
    }

    void Start()
    {
        Play("Music");//plays the sound called music
    }

    public void Play(string name)//plays sounds 
    {
        Sound s = Array.Find(sounds, sound => sound.name == name);//finds the specified sound in the array
        if (s == null)
        {
            Debug.LogWarning("Sound" + s + "not found.");//if sound cant be found
            return; 
        }
        s.source.Play();//plays the sound
    }

    
}
