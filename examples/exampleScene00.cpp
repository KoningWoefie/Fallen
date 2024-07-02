#include "exampleScene00.h"
#include "SQLAPI.h"
#include "examples/testobj.h"
#include "src/Presets/button.h"
#include "src/Presets/canvas.h"
#include "src/UI/uielement.h"
#include <src/UI/image.h>
#include <sys/_select.h>

ExampleScene00::ExampleScene00()
{
    canvas = new Presets::Canvas(glm::vec2(1280, 720));

    button = new Presets::Button("assets/RunButton.tga");

    button->transform->position = glm::vec3(0.0f, 0.0f, 0.0f);

    FallenUI::Button* b = button->GetComponent<FallenUI::Button>();
    b->SetOnHover(std::bind(&ExampleScene00::OnButtonHovered, this));
    b->SetOnPress(std::bind(&ExampleScene00::OnButtonClicked, this));
    b->SetOnRelease(std::bind(&ExampleScene00::OnButtonReleased, this));

    // AnimatedSprite* sprite = new AnimatedSprite("assets/Sprite_Sheet_G4.tga", 4, 4, 0.5f);
    // FallenUI::Image* i = button->GetComponent<FallenUI::Image>();
    // i->AddSprite(sprite);
    // sprite->AddAnimation({1,2,3,4});
    // i = nullptr;

    button->AddComponent(new Text());
    Text* t = button->GetComponent<Text>();
    t->text = "Heppo World!";

    AddChild(canvas);
    canvas->AddChild(button);

    button->GetComponent<FallenUI::UIElement>()->SetAlignment(FallenUI::UIAlignment::Center);

    sql = new SQL("test", "root", "root", "Rooms");
    GetDatabaseValue();
}

ExampleScene00::~ExampleScene00()
{
}

void ExampleScene00::GetDatabaseValue()
{
    std::vector<std::string> fields = {"Room_ID", "Room_Name", "Room_Password", "Room_Member_Count", "Room_Current_Member", "Room_Last_Card", "Room_Creation_Time", "Room_Expiry_Time", "Room_Last_Edited_Time"};
    std::vector<std::string> values = {"", "Inserted", "1234", "0", "0", "0", "", "2024-09-22 00:00:00.000", ""};
    std::vector<SQLType> types = {SQLType::DEFAULT, SQLType::STRING, SQLType::STRING, SQLType::INT, SQLType::INT, SQLType::INT, SQLType::DEFAULT, SQLType::DATETIME, SQLType::DEFAULT};
    // sql->CreateRow(fields, values, types);
    // int i = sql->SelectData<int>("Room_Member_Count", "`Room_Expiry_Time` = '2024-09-22 00:00:00.000'");
    // SADateTime dt = sql->SelectData<SADateTime>("Room_Expiry_Time");
    sql->DeleteRow("`Room_ID` = '13'");
}

void ExampleScene00::Update(float deltaTime)
{
    if(Input()->GetKey(KeyCode::D))
    {
        button->transform->position.x += 10.0f * deltaTime;
        // dynamic_cast<SpriteSheet*>(button->GetComponent<FallenUI::Image>()->GetSprite())->SetCurrentFrame(2);
    }
}

void ExampleScene00::OnButtonClicked()
{
    std::cout << "Button Clicked!" << "\n";
}

void ExampleScene00::OnButtonHovered()
{
    std::cout << "Button Hovered!" << "\n";
}

void ExampleScene00::OnButtonReleased()
{
    std::cout << "Button Released!" << "\n";
}
