#include "gamepickerScene.h"
#include "defaultObject.h"
#include "src/uielement.h"
#include <src/image.h>

GamePickerScene::GamePickerScene()
{
	_canvas = new DefaultObject();
	_canvas->AddComponent(new Canvas(glm::vec2(1280, 720)));
	this->AddChild(_canvas);
	_button = new DefaultObject();
	Image* i = new Image();
	i->AddSprite(new Sprite("assets/buttonFrame.tga"));
	_button->AddComponent(i);

	Button* b = new Button(256, 256);
	b->SetOnHover(std::bind(&GamePickerScene::OnButtonHovered, this));
	b->SetOnPress(std::bind(&GamePickerScene::OnButtonClicked, this));
	b->SetOnRelease(std::bind(&GamePickerScene::OnButtonReleased, this));
	_button->AddComponent(b);
	_canvas->AddChild(_button);
	_button->GetComponent<UIElement>()->SetAlignment(UIAlignment::Center);
	i = nullptr;
	b = nullptr;
}

GamePickerScene::~GamePickerScene()
{
	delete _canvas;
	_canvas = nullptr;
	delete _button;
	_button = nullptr;
}

void GamePickerScene::Update(float deltaTime)
{
	if (Input()->GetKeyDown(KeyCode::Right)) _button->GetComponent<Button>()->Select();
}

void GamePickerScene::OnButtonClicked()
{
    std::cout << "Button Clicked!" << std::endl;
}

void GamePickerScene::OnButtonHovered()
{
    std::cout << "Button Hovered!" << std::endl;
}

void GamePickerScene::OnButtonReleased()
{
    std::cout << "Button Released!" << std::endl;
}
