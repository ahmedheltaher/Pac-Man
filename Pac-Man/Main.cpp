#include "./headers/Main.h"

void mainMenu() {
    sf::RenderWindow mainMenuWindow(VIDEOMODE, TITLE);
    setupLogo(mainMenuWindow);
    sf::Thread gameThread(&gameLoop),
        instructionsThread(&instructions), leaderBoardThread(&leaderBoard),
        creditsThread(&credits), enterYourNameThread(&enterYourName);
    Menu menu("Joystix", 40, 450, 400, 400, 400, true);
    menu.addNewItem("Play", [&]() {
        enterYourNameMutex.lock();
        mainMenuWindow.close();
        enterYourNameThread.launch();
        enterYourNameMutex.unlock();
    });
    menu.addNewItem("Instruction", [&]() {
        instructionsMutex.lock();
        mainMenuWindow.close();
        instructionsThread.launch();
        instructionsMutex.unlock();
    });
    menu.addNewItem("Leader Board", [&]() {
        leaderBoardMutex.lock();
        mainMenuWindow.close();
        leaderBoardThread.launch();
        leaderBoardMutex.unlock();
    });
    menu.addNewItem("Credits", [&]() {
        creditsMutex.lock();
        mainMenuWindow.close();
        creditsThread.launch();
        creditsMutex.unlock();
    });
    menu.addNewItem("Exit", [&]() {
        mainMenuWindow.close();
    });

    sf::Texture logotexture;
    logotexture.loadFromFile("./textures/start_logo.png");
    sf::Sprite logoSprite(logotexture);
    logoSprite.setPosition(sf::Vector2f(400, 50));

    sf::Texture imagetexture;
    imagetexture.loadFromFile("./textures/satrt_image.png");
    sf::Sprite imageSprite(imagetexture);
    imageSprite.setScale((float) 0.7, (float) 0.7);
    imageSprite.setPosition(sf::Vector2f(550, 150));

    while (mainMenuWindow.isOpen()) {
        sf::Event event;
        while (mainMenuWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                mainMenuWindow.close();
                break;
            case sf::Event::KeyPressed:
                soundManager.playSFX("menu");
                menu.handleEvents(event);
            }
        }
        mainMenuWindow.clear();
        menu.draw(mainMenuWindow);
        mainMenuWindow.draw(logoSprite);
        mainMenuWindow.draw(imageSprite);
        mainMenuWindow.display();
    }
};

void instructions() {
    instructionsMutex.lock();
    sf::Thread mainMenuThread(&mainMenu);
    sf::RenderWindow instructionsWindow(VIDEOMODE, TITLE + " - Instructions");
    setupLogo(instructionsWindow);
    Menu controlMenu("Joystix", 40, 1100, 100, 400, 400, true);
    controlMenu.addNewItem("Back", [&]() {
        instructionsWindow.close();
        mainMenuThread.launch();
    });
    controlMenu.addNewItem("Exit", [&]() {
        instructionsWindow.close();
    });
    Menu textMenu("Joystix", 60, 0, 100, 400, 700, false);
    textMenu.addNewItem("\t\tGoaL\nGuide Pacman around \nthe maze and eat \nall the little white\ndots whilst avoiding \nthose nasty ghosts.\n \t  Contols\nWASD keys for Pacman \nEsc : Pause game \n ", []() {});

    while (instructionsWindow.isOpen()) {
        sf::Event event;
        while (instructionsWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                instructionsWindow.close();
                break;
            case sf::Event::KeyPressed:
                soundManager.playSFX("menu");
                controlMenu.handleEvents(event);
                break;
            default:
                break;
            }
        }
        instructionsWindow.clear();
        controlMenu.draw(instructionsWindow);
        textMenu.draw(instructionsWindow);
        instructionsWindow.display();
    }
    instructionsMutex.unlock();
};

void leaderBoard() {
    leaderBoardMutex.lock();
    sf::Thread mainMenuThread(&mainMenu);
    sf::RenderWindow leaderBoardWindow(VIDEOMODE, TITLE + " - Leader Board");
    setupLogo(leaderBoardWindow);
    Menu controlMenu("Joystix", 40, 1100, 100, 400, 400, true);
    controlMenu.addNewItem("Back", [&]() {
        leaderBoardWindow.close();
        mainMenuThread.launch();
        });
    controlMenu.addNewItem("Exit", [&]() {
        leaderBoardWindow.close();
        });
    Menu leaderBoardMenu("Joystix", 60, 0, 100, 400, 700, false);
    std::string data = storage.getStringLeaderBoard();
    leaderBoardMenu.addNewItem(data, []() {});

    while (leaderBoardWindow.isOpen()) {
        sf::Event event;
        while (leaderBoardWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                leaderBoardWindow.close();
                break;
            case sf::Event::KeyPressed:
                soundManager.playSFX("menu");
                controlMenu.handleEvents(event);
                break;
            default:
                break;
            }
        }
        leaderBoardWindow.clear();
        controlMenu.draw(leaderBoardWindow);
        leaderBoardMenu.draw(leaderBoardWindow);
        leaderBoardWindow.display();
    }
    leaderBoardMutex.unlock();
};

void credits() {
    creditsMutex.lock();
    sf::Thread mainMenuThread(&mainMenu);
    sf::RenderWindow creditsWindow(VIDEOMODE, TITLE + " - Credits");
    setupLogo(creditsWindow);
    Menu controlMenu("Joystix", 40, 1100, 100, 400, 400, true);
    controlMenu.addNewItem("Back", [&]() {
        creditsWindow.close();
        mainMenuThread.launch();
        });
    controlMenu.addNewItem("Exit", [&]() {
        creditsWindow.close();
        });
    Menu leaderBoardMenu("Joystix", 40, 0, 100, 400, 700, false);
    leaderBoardMenu.addNewItem("This game developed by \n \tAhmed Eltaher \nRelease date : 1/4/2021 ", []() {});

    while (creditsWindow.isOpen()) {
        sf::Event event;
        while (creditsWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                creditsWindow.close();
                break;
            case sf::Event::KeyPressed:
                soundManager.playSFX("menu");
                controlMenu.handleEvents(event);
                break;
            default:
                break;
            }
        }
        creditsWindow.clear();
        controlMenu.draw(creditsWindow);
        leaderBoardMenu.draw(creditsWindow);
        creditsWindow.display();
    }
    creditsMutex.unlock();
};

void enterYourName() {
    enterYourNameMutex.lock();
    sf::Thread mainMenuThread(&mainMenu), gameThread(&gameLoop);
    sf::Clock clock;
    static sf::Time textEffectTime;
    static bool showCursor;
    sf::RenderWindow enterYourNameWindow(VIDEOMODE, TITLE + " - Enter Your Name");
    setupLogo(enterYourNameWindow);
    Menu controlMenu("Joystix", 40, 1100, 100, 400, 400, true);
    controlMenu.addNewItem("Continue", [&]() {
        gameMutex.lock();
        enterYourNameWindow.close();
        gameThread.launch();
        gameMutex.unlock();
    });
    controlMenu.addNewItem("Back", [&]() {
        enterYourNameWindow.close();
        mainMenuThread.launch();
    });
    controlMenu.addNewItem("Exit", [&]() {
        enterYourNameWindow.close();
    });
    Menu inputMenu("Joystix", 40, 0, 100, 400, 700, false);
    inputMenu.addNewItem("Enter Your Name (max 10 chars)", []() {});
    inputMenu.addNewItem(playerName, []() {});

    while (enterYourNameWindow.isOpen()) {
        sf::Event event;
        while (enterYourNameWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                enterYourNameWindow.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!playerName.empty()) {
                        playerName.pop_back();
                        playerNameLength--;
                    }
                }
                if (std::isprint(event.text.unicode)) soundManager.playSFX("menu");
                controlMenu.handleEvents(event);
                break;
            case sf::Event::TextEntered:
                if (playerNameLength < 10 && std::isprint(event.text.unicode)) {
                    playerName += event.text.unicode;
                    playerNameLength++;
                }
                break;
            default:
                break;
            }
        }

        textEffectTime += clock.restart();

        if (textEffectTime >= sf::seconds(0.5f)) {
            showCursor = !showCursor;
            textEffectTime = sf::Time::Zero;
        }
        inputMenu.updateItem(1, playerName + (showCursor ? '_' : ' '));
        enterYourNameWindow.clear();
        controlMenu.draw(enterYourNameWindow);
        inputMenu.draw(enterYourNameWindow);
        enterYourNameWindow.display();
    }
    enterYourNameMutex.unlock();
};

void win() {
    winMutex.lock();
    sf::Thread mainMenuThread(&mainMenu);
    sf::RenderWindow winWindow(VIDEOMODE, TITLE + " - You Won!");
    setupLogo(winWindow);
    Menu controlMenu("Joystix", 40, 400, 400, 400, 400, true);
    controlMenu.addNewItem("Back to main Menu", [&]() {
        winWindow.close();
        mainMenuThread.launch();
        });
    controlMenu.addNewItem("Exit", [&]() {
        winWindow.close();
        });
    Menu leaderBoardMenu("Joystix", 80, 400, 100, 400, 700, false);
    leaderBoardMenu.addNewItem("You Won!", []() {});

    while (winWindow.isOpen()) {
        sf::Event event;
        while (winWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                winWindow.close();
                break;
            case sf::Event::KeyPressed:
                soundManager.playSFX("menu");
                controlMenu.handleEvents(event);
                break;
            default:
                break;
            }
        }
        winWindow.clear();
        controlMenu.draw(winWindow);
        leaderBoardMenu.draw(winWindow);
        winWindow.display();
    }
    winMutex.unlock();
};

void lose() {
    loseMutex.lock();
    sf::Thread mainMenuThread(&mainMenu);
    sf::RenderWindow loseWindow(VIDEOMODE, TITLE + " - You Lost");
    setupLogo(loseWindow);
    Menu controlMenu("Joystix", 40, 400, 400, 400, 400, true);
    controlMenu.addNewItem("Back to main Menu", [&]() {
        loseWindow.close();
        mainMenuThread.launch();
        });
    controlMenu.addNewItem("Exit", [&]() {
        loseWindow.close();
        });
    Menu leaderBoardMenu("Joystix", 80, 400, 100, 400, 700, false);
    leaderBoardMenu.addNewItem("You Lost", []() {});

    while (loseWindow.isOpen()) {
        sf::Event event;
        while (loseWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                loseWindow.close();
                break;
            case sf::Event::KeyPressed:
                soundManager.playSFX("menu");
                controlMenu.handleEvents(event);
                break;
            default:
                break;
            }
        }
        loseWindow.clear();
        controlMenu.draw(loseWindow);
        leaderBoardMenu.draw(loseWindow);
        loseWindow.display();
    }
    loseMutex.unlock();
};

void gameLoop() {
    gameMutex.lock();
    sf::Thread mainMenuThread(&mainMenu);
    sf::Thread winThread(&win), loseThread(&lose);
    sf::RenderWindow gameWindow(VIDEOMODE, TITLE);
    setupLogo(gameWindow);
    FPS fps;
    sf::Clock clock;
    sf::Time time;
    float deltaTime = 0;
    soundManager.playMusic("mainTheme");
    bool whiteSpacesOnly = std::all_of(playerName.begin(), playerName.end(), isspace);
    playerName = (playerName == "" || whiteSpacesOnly) ? "Unknow" : playerName;
    Menu sideMenu("Joystix", 20, 1250, 50, 250, 200, false);
    sideMenu.addNewItem("Player: \n" + playerName, []() {});
    sideMenu.addNewItem("FPS: 0", []() {});
    sideMenu.addNewItem("Score: 0", []() {});
    sideMenu.addNewItem("Lives: 0", []() {});

    Menu pauseMenu("Joystix", 40, 600, 300, 100, 400, true);
    pauseMenu.addNewItem("Resume", [&]() {
        gamePaused = false;
        level.pause();
        soundManager.playBack();
    });
    pauseMenu.addNewItem("Back To Main Menu", [&]() {
        gameWindow.close();
        mainMenuThread.launch();
    });
    pauseMenu.addNewItem("Exit", [&]() {
        gameWindow.close();
    });
    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                gameWindow.close();
                soundManager.pause();
                break;
            case sf::Event::LostFocus:
                gamePaused = true;
                soundManager.pause();
                break;
            case sf::Event::GainedFocus:
                gamePaused = false;
                level.pause();
                soundManager.playBack();
                break;
            case sf::Event::KeyPressed:
                if (gamePaused) {
                    soundManager.playSFX("menu");
                    pauseMenu.handleEvents(event);
                    soundManager.pause();

                }
                if (event.key.code == sf::Keyboard::Escape) {
                    if (gamePaused) {
                        gamePaused = false;
                        level.pause();
                        soundManager.playBack();
                    }
                    else {
                        gamePaused = true;
                        soundManager.pause();
                    }
                }
                level.handleEvents(event);
                break;
            default:
                break;
            }
        }
        gameWindow.clear();
        if (!gamePaused) {
            sideMenu.updateItem(1, "FPS: " + std::to_string(fps.getFPS()));
            sideMenu.updateItem(2, "Score: " + std::to_string(level.getScore()));
            sideMenu.updateItem(3, "Lives: " + std::to_string(level.pacman.getLives()));
            level.draw(&gameWindow);
            sideMenu.draw(gameWindow);
            level.update(deltaTime);
            if (level.gotAllCoins()) {
                winMutex.lock();
                winThread.launch();
                gameWindow.close();
                winMutex.unlock();
                soundManager.pause();
                storage.addData(playerName + " " + std::to_string(level.getScore()));
            }
            if (level.pacmanDied()) {
                loseMutex.lock();
                loseThread.launch();
                gameWindow.close();
                loseMutex.unlock();
                soundManager.pause();
                storage.addData(playerName + " " + std::to_string(level.getScore()));
            }

            fps.update();
            time = clock.restart();
            deltaTime = time.asSeconds();
        }
        else {
            pauseMenu.draw(gameWindow);
        }
        gameWindow.display();
    }
    gameMutex.unlock();
};

int main() {
    mainMenu();
    return EXIT_SUCCESS;
};