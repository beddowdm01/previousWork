/*A class to handle all audio within the game*/
using System;
using UnityEngine;
using System.Collections.Generic;

public class AudioManager : MonoBehaviour
{

    public Sound[] sounds; //creates an array of Sounds
    public static AudioManager Instance;
    public float MasterVolume = 1f;

    private List<Sound> musicTracks = new List<Sound>();
    private int currentMusicIndex = 0;
    private Sound currentMusicTrack;

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


        DontDestroyOnLoad(gameObject);//allows it to persist through levels   fdsfd

        foreach (Sound s in sounds)//loops through the sound array
        {
            s.source = gameObject.AddComponent<AudioSource>();
            s.source.clip = s.clip;
            s.source.volume = s.volume;
            s.source.spatialBlend = s.spatialblend;
            s.source.pitch = s.pitch;
            s.source.loop = s.loop;
            if (s.SoundType == Sound.Type.Music)
            {
                musicTracks.Add(s);
            }
        }
    }

    private void Start()
    {
        PlayBackgroundMusic();
    }

    private void Update()
    {
        if (currentMusicTrack.source.isPlaying == false)
        {
            PlayBackgroundMusic();
        }
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

    public void ChangeVolume(string name, float newVolume)
    {
        Sound s = Array.Find(sounds, sound => sound.name == name);//finds the specified sound in the array
        if (s == null)
        {
            Debug.LogWarning("Sound" + s + "not found.");//if sound cant be found
            return;
        }
        s.source.volume = newVolume;
    }

    public void ChangeAudioVolume(float newVolume, Sound.Type soundType)
    {
        foreach (Sound s in sounds)
        {
            if (s.SoundType == soundType)
            {
                s.source.volume = newVolume * MasterVolume;
            }
        }
    }

    public void ChangeMasterVolume(float newVolume)//changes the master volume
    {
        foreach (Sound s in sounds)
        {
            s.source.volume = s.source.volume / MasterVolume;
            Debug.Log(s.source.volume);
            s.source.volume = s.source.volume * newVolume;
            Debug.Log(s.source.volume);
        }
        MasterVolume = newVolume;

    }

    public void PlayBackgroundMusic()//plays every music track one after the other after purring them in a list.
    {
        if (currentMusicIndex >= musicTracks.Count)
        {
            currentMusicIndex = 0;
        }
        currentMusicTrack = musicTracks[currentMusicIndex];
        Play(musicTracks[currentMusicIndex].name);
        currentMusicIndex++;
    }
}
