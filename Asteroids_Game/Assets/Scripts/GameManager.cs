using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

// Keeps track of the overall game like the lives score etc..


public class GameManager : MonoBehaviour
{
    public AsteroidSpawner spawner;
    public Player player;
    public int lives = 3;
    public float respawnTime = 3.0f;
    public float respawnInvulnerabilityTime = 3.0f;
    public ParticleSystem explosion;
    public int score = 0;

    public Text scoreText;
    public Text livesText;

    void Start()
    {
        SetScore();
        SetLives();
    }

    private void SetScore()
    {
        scoreText.text = "Score " + this.score;
    }

    private void SetLives()
    {
        livesText.text = "Lives " + this.lives;
    }

    public void AsteroidDestroyed(Asteroid asteroid)
    {
        this.explosion.transform.position = asteroid.transform.position;
        this.explosion.Play();

        // smaller asteroids more points
        if (asteroid.size < 0.75f)
            score += 100;
        else if (asteroid.size < 1.25f)
            score += 50;
        else
            score += 25;

        SetScore();

        if (score > 500 && score <= 600)
            spawner.DecreaseSpawnRate();

    }

    public void PlayerDied()
    {
        // doing explosion in GameManager coz - we cant do it in
        // Asteroid as it is a prefab
        this.explosion.transform.position = this.player.transform.position;
        this.explosion.Play();

        this.lives--; SetLives();

        if(this.lives <= 0)
            GameOver();
        else
            Invoke(nameof(Respawn), this.respawnTime);
    }

    private void Respawn()
    {
        this.player.transform.position = Vector3.zero;
        // to avoid colllisions in the first few secs afterr respawning
        this.player.gameObject.layer = LayerMask.NameToLayer("Ignore Collisions");
       
        this.player.gameObject.SetActive(true);

        Invoke(nameof(TurnOnCollisions), this.respawnInvulnerabilityTime);
    }

    private void TurnOnCollisions()
    {
        this.player.gameObject.layer = LayerMask.NameToLayer("Player");
    }

    private void GameOver()
    {
        this.lives = 3; SetLives();
        this.score = 0; SetScore();

        Invoke(nameof(Respawn), this.respawnTime);
    }
}
