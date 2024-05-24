const config = {
    type: Phaser.AUTO,
    width: 800,
    height: 600,
    physics: {
        default: 'arcade',
        arcade: {
            gravity: { y: 0 },
            debug: false
        }
    },
    scene: {
        preload: preload,
        create: create,
        update: update
    }
};

const game = new Phaser.Game(config);

let player;
let cursors;
let asteroids;
let fuels;
let bullets;
let score = 0;
let scoreText;
let fuelText;
let timeText;
let levelText;
let bestScore = 0;

function preload() {
    this.load.image('background', 'Sprites/bg.png');
    this.load.image('missile', 'Sprites/misiles.png');
    this.load.image('lifeBar', 'Sprites/Lifebar.png');
    this.load.audio('music', 'sonidos/saitama.ogg');
    this.load.audio('fuelSound', 'sonidos/combustible.ogg');
    this.load.audio('missileSound', 'sonidos/misilsound.ogg');
    this.load.audio('lowFuelSound', 'sonidos/lowfuel.ogg');
    this.load.audio('collisionSound', 'sonidos/Colision_Asteroide.ogg');
    this.load.audio('explosionSound', 'sonidos/Explosion.ogg');
}

function create() {
    this.add.image(400, 300, 'background');
    player = this.physics.add.sprite(100, 450, 'missile').setScale(0.5);
    player.setCollideWorldBounds(true);

    asteroids = this.physics.add.group();
    fuels = this.physics.add.group();
    bullets = this.physics.add.group();

    cursors = this.input.keyboard.createCursorKeys();
    
    scoreText = this.add.text(16, 16, 'Score: 0', { fontSize: '20px', fill: '#fff' });
    fuelText = this.add.text(16, 50, 'Fuel: 100%', { fontSize: '20px', fill: '#fff' });
    timeText = this.add.text(670, 16, 'Time: 0s', { fontSize: '20px', fill: '#fff' });
    levelText = this.add.text(525, 16, 'Level: 1', { fontSize: '20px', fill: '#fff' });

    // Add collision detection
    this.physics.add.collider(player, asteroids, hitAsteroid, null, this);
    this.physics.add.overlap(player, fuels, collectFuel, null, this);
    this.physics.add.overlap(bullets, asteroids, shootAsteroid, null, this);
    
    this.music = this.sound.add('music');
    this.music.play({ loop: true, volume: 0.1 });

    this.fuelSound = this.sound.add('fuelSound');
    this.missileSound = this.sound.add('missileSound');
    this.lowFuelSound = this.sound.add('lowFuelSound');
    this.collisionSound = this.sound.add('collisionSound');
    this.explosionSound = this.sound.add('explosionSound');

    this.time.addEvent({
        delay: 1000,
        callback: updateTime,
        callbackScope: this,
        loop: true
    });
    
    spawnAsteroids(this, 15);
}

function update() {
    if (cursors.left.isDown) {
        player.setVelocityX(-200);
    } else if (cursors.right.isDown) {
        player.setVelocityX(200);
    } else {
        player.setVelocityX(0);
    }

    if (cursors.up.isDown) {
        player.setVelocityY(-200);
    } else if (cursors.down.isDown) {
        player.setVelocityY(200);
    } else {
        player.setVelocityY(0);
    }

    if (Phaser.Input.Keyboard.JustDown(cursors.space)) {
        shootMissile(this);
    }
}

function updateTime() {
    // Update the timer and other time-dependent elements here
}

function hitAsteroid(player, asteroid) {
    this.collisionSound.play();
    asteroid.destroy();
    // Handle player hit logic here
}

function collectFuel(player, fuel) {
    this.fuelSound.play();
    fuel.destroy();
    // Handle fuel collection logic here
}

function shootAsteroid(bullet, asteroid) {
    this.collisionSound.play();
    bullet.destroy();
    asteroid.destroy();
    // Handle shooting asteroid logic here
}

function shootMissile(scene) {
    let bullet = scene.physics.add.sprite(player.x, player.y, 'missile').setScale(0.2);
    bullet.setVelocityX(400);
    bullets.add(bullet);
    scene.missileSound.play();
}

function spawnAsteroids(scene, number) {
    for (let i = 0; i < number; i++) {
        let x = Phaser.Math.Between(800, 1600);
        let y = Phaser.Math.Between(0, 600);
        let asteroid = scene.physics.add.image(x, y, 'missile').setScale(0.5);
        asteroid.setVelocityX(Phaser.Math.Between(-200, -100));
        asteroids.add(asteroid);
    }
}
