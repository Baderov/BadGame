#include "Authorization.h" // подключаем заголовочный файл.

void authorization(GameVariables* gv)
{
	gv->playerName = "";
	int menuNum = 0, nickSize = 0;
	bool input = false;
	sf::Color blackTransparent(0, 0, 0, 50);
	sf::RectangleShape authRS, nicknameRS, loginRS, exitRS;
	authRS.setFillColor(blackTransparent);
	authRS.setSize(sf::Vector2f(450.f, 450.f));
	authRS.setOrigin(authRS.getSize().x / 2.f, authRS.getSize().y / 2.f);
	authRS.setPosition(gv->window.getSize().x / 2.f, gv->window.getSize().y / 2.f);

	loginRS.setSize(sf::Vector2f(150.f, 50.f));
	loginRS.setOrigin(loginRS.getSize().x / 2.f, loginRS.getSize().y / 2.f);
	loginRS.setPosition(authRS.getPosition().x - 100.f, authRS.getPosition().y + 170.f);

	exitRS.setSize(sf::Vector2f(150.f, 50.f));
	exitRS.setOrigin(exitRS.getSize().x / 2.f, exitRS.getSize().y / 2.f);
	exitRS.setPosition(authRS.getPosition().x + 100.f, authRS.getPosition().y + 170.f);

	sf::Text enterYourNameText, nicknameText, loginText, exitText;
	enterYourNameText.setFont(gv->consolasFont);
	enterYourNameText.setString("ENTER YOUR NAME");
	enterYourNameText.setStyle(sf::Text::Bold);
	enterYourNameText.setCharacterSize(50);
	enterYourNameText.setFillColor(sf::Color::Black);
	enterYourNameText.setOrigin(round(enterYourNameText.getLocalBounds().left + (enterYourNameText.getLocalBounds().width / 2.f)), round(enterYourNameText.getLocalBounds().top + (enterYourNameText.getLocalBounds().height / 2.f)));
	enterYourNameText.setPosition(authRS.getPosition().x, authRS.getPosition().y - 170.f);

	loginText.setFont(gv->consolasFont);
	loginText.setString("LOGIN");
	loginText.setStyle(sf::Text::Bold);
	loginText.setCharacterSize(40);
	loginText.setFillColor(sf::Color::Black);
	loginText.setOrigin(round(loginText.getLocalBounds().left + (loginText.getLocalBounds().width / 2.f)), round(loginText.getLocalBounds().top + (loginText.getLocalBounds().height / 2.f)));
	loginText.setPosition(loginRS.getPosition());

	exitText.setFont(gv->consolasFont);
	exitText.setString("EXIT");
	exitText.setStyle(sf::Text::Bold);
	exitText.setCharacterSize(40);
	exitText.setFillColor(sf::Color::Black);
	exitText.setOrigin(round(exitText.getLocalBounds().left + (exitText.getLocalBounds().width / 2.f)), round(exitText.getLocalBounds().top + (exitText.getLocalBounds().height / 2.f)));
	exitText.setPosition(exitRS.getPosition());

	nicknameRS.setFillColor(sf::Color::White);
	nicknameRS.setSize(sf::Vector2f(400.f, 50.f)); // устанавливаем размер фигуры.
	nicknameRS.setOrigin(nicknameRS.getSize().x / 2.f, nicknameRS.getSize().y / 2.f); // устанавливаем размер фигуры.
	nicknameRS.setPosition(enterYourNameText.getPosition().x, enterYourNameText.getPosition().y + 170.f); // устанавливаем позицию для фигуры.

	nicknameText.setFont(gv->consolasFont);
	nicknameText.setString("");
	nicknameText.setStyle(sf::Text::Bold);
	nicknameText.setCharacterSize(45);
	nicknameText.setFillColor(sf::Color::Black);
	nicknameText.setPosition((nicknameRS.getPosition().x - (nicknameRS.getSize().x / 2.f)) + 5.f, nicknameRS.getPosition().y - 83.f);


	while (gv->window.isOpen()) // пока открыто окно.
	{
		sf::Vector2f mousePos = gv->window.mapPixelToCoords(sf::Mouse::getPosition(gv->window)); // переводим их в игровые (уходим от коорд окна)
		menuNum = 0;
		loginRS.setFillColor(sf::Color::White);
		exitRS.setFillColor(sf::Color::White);

		if (nicknameRS.getGlobalBounds().contains(mousePos.x, mousePos.y)) {  menuNum = 1; }
		if (loginRS.getGlobalBounds().contains(mousePos.x, mousePos.y)) { loginRS.setFillColor(sf::Color::Yellow); menuNum = 2; }
		if (exitRS.getGlobalBounds().contains(mousePos.x, mousePos.y)) { exitRS.setFillColor(sf::Color::Yellow); menuNum = 3; }

		while (gv->window.pollEvent(gv->event)) // пока происходят события.
		{
			authKeyboard(gv, gv->event, nicknameText, input);
			if (gv->event.type == sf::Event::Closed)
			{
				gv->window.close();
			}
			if (gv->event.type == sf::Event::MouseButtonPressed && gv->event.mouseButton.button == sf::Mouse::Left) // если нажали левую кнопку мыши.
			{
				if (menuNum == 0)
				{
					nicknameRS.setFillColor(sf::Color::White);
					input = false;
				}
				if (menuNum == 1)
				{
					nicknameRS.setFillColor(sf::Color::Green);
					input = true;
				}
				if (menuNum == 2)
				{
					if (gv->playerName.length() >= 1)
					{
						nicknameRS.setFillColor(sf::Color::White);
						menuNum = 0;
						return;
					}
				}
				if (menuNum == 3)
				{
					gv->window.close();
				}
			}
		}
		gv->window.clear(sf::Color::Cyan); // очистка окна.
		gv->window.draw(authRS); 
		gv->window.draw(loginRS);
		gv->window.draw(exitRS);
		gv->window.draw(nicknameRS);
		gv->window.draw(exitText);
		gv->window.draw(enterYourNameText); 
		gv->window.draw(loginText);
		gv->window.draw(nicknameText);
		gv->window.display(); // отображает кадр.
	}
}