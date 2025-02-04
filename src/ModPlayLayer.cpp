#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>
#include <Geode/modify/GameObject.hpp>

using namespace geode::prelude;

class $modify(ModPlayLayer, PlayLayer) {
public:
    struct Fields {
        CCLabelBMFont* objectTotalLabel = nullptr;  // Это поле будет доступно через m_fields
        CCLabelBMFont* objectActiveLabel = nullptr;  // Это поле будет доступно через m_fields
    };

    void onEnterTransitionDidFinish() override {
        PlayLayer::onEnterTransitionDidFinish();  // Вызов базового метода
        updateObjectCounter();
    }

    void updateObjectCounter() {
        // Удаляем старый текст, если он существует
        if (this->m_fields->objectTotalLabel) {
            this->removeChildByTag(1001);
        }
        if (this->m_fields->objectActiveLabel) {
            this->removeChildByTag(1002);
        }

        int totalObjects = 0;
        int activeObjects = 0;

        // Подсчет общего количества объектов
        if (this->m_objects) {
            CCObject* obj = nullptr;
            CCARRAY_FOREACH(this->m_objects, obj) {
                if (dynamic_cast<GameObject*>(obj)) {
                    totalObjects++;
                }
            }
        }

        // Создаем и обновляем текст для общего числа объектов
        this->m_fields->objectTotalLabel = CCLabelBMFont::create(
            ("Total: " + std::to_string(totalObjects)).c_str(),
            "bigFont.fnt"
        );
        this->m_fields->objectTotalLabel->setPosition({5, CCDirector::sharedDirector()->getWinSize().height - (Mod::get()->getSettingValue<int>("total-delta-pos")*10)});
        this->m_fields->objectTotalLabel->setAnchorPoint({0, 1});
        this->m_fields->objectTotalLabel->setScale(0.05f * Mod::get()->getSettingValue<int>("total-size"));
        this->m_fields->objectTotalLabel->setOpacity(Mod::get()->getSettingValue<int>("total-opacity"));;
        this->m_fields->objectTotalLabel->setTag(1001);

        // Создаем и обновляем текст для активных объектов
        this->m_fields->objectActiveLabel = CCLabelBMFont::create(
            ("Active: " + std::to_string(this->m_activeObjects)).c_str(),
            "bigFont.fnt"
        );
        this->m_fields->objectActiveLabel->setPosition({5, CCDirector::sharedDirector()->getWinSize().height - (Mod::get()->getSettingValue<int>("active-delta-pos")*10)});
        this->m_fields->objectActiveLabel->setAnchorPoint({0, 1});
        this->m_fields->objectActiveLabel->setScale(0.05f * Mod::get()->getSettingValue<int>("active-size"));
        this->m_fields->objectActiveLabel->setOpacity(Mod::get()->getSettingValue<int>("active-opacity"));
        this->m_fields->objectActiveLabel->setTag(1002);

        // Добавление текста на сцену
        this->addChild(this->m_fields->objectTotalLabel, 100);
        this->addChild(this->m_fields->objectActiveLabel, 101);
    }

    void updateActiveObjects() {
        if (this->m_fields->objectActiveLabel) {
            this->m_fields->objectActiveLabel->setString(("Active: " + std::to_string(this->m_activeObjects)).c_str());
        }
    }

    void onQuit() {
        // Удаляем текстовые элементы, если они существуют
        if (this->m_fields->objectTotalLabel) {
            this->removeChildByTag(1001);
        }
        if (this->m_fields->objectActiveLabel) {
            this->removeChildByTag(1002);
        }
        PlayLayer::onQuit();  // Вызов базового метода
    }

    void updateInfoLabel() {
        updateActiveObjects();
    }
};
