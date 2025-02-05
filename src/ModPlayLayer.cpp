#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>
#include <Geode/modify/GameObject.hpp>

using namespace geode::prelude;

class $modify(ModPlayLayer, PlayLayer) {
public:
    struct Fields {
        CCLabelBMFont* objectTotalLabel = nullptr;
        CCLabelBMFont* triggerTotalLabel = nullptr;
        CCLabelBMFont* objectActiveLabel = nullptr;
        CCLabelBMFont* particleActiveLabel = nullptr;

        CCArray* m_triggers = nullptr;

        Fields() {
            m_triggers = CCArray::create();
            m_triggers->retain();
        }
        ~Fields() {
            if (m_triggers) {
                m_triggers->release(); // Освобождаем память в деструкторе
            }
        }
    };

    void onEnterTransitionDidFinish() override {
        updateObjectCounter();
        PlayLayer::onEnterTransitionDidFinish();
    }

    void updateObjectCounter() {
        if (this->m_fields->objectTotalLabel) {
            this->removeChildByTag(1001);
        }
        if (this->m_fields->triggerTotalLabel) {
            this->removeChildByTag(1002);
        }
        if (this->m_fields->objectActiveLabel) {
            this->removeChildByTag(1003);
        }
        if (this->m_fields->particleActiveLabel) {
            this->removeChildByTag(1004);
        }

        int totalObjects = 0;
        int totalTriggers = 0;

        if (this->m_objects) {
            CCObject* obj = nullptr;
            CCARRAY_FOREACH(this->m_objects, obj) {
                if (auto gameObject = dynamic_cast<GameObject*>(obj)) {
                    totalObjects++;
                    if (gameObject->isTrigger()) {
                        totalTriggers++;
                    }
                }
            }
        }

        this->m_fields->objectTotalLabel = CCLabelBMFont::create(
            ("Total Objects: " + std::to_string(totalObjects)).c_str(),
            "bigFont.fnt"
        );
        this->m_fields->objectTotalLabel->setPosition({5, CCDirector::sharedDirector()->getWinSize().height - (Mod::get()->getSettingValue<int>("total-objects-delta-pos")*10)});
        this->m_fields->objectTotalLabel->setAnchorPoint({0, 1});
        this->m_fields->objectTotalLabel->setScale(0.05f * Mod::get()->getSettingValue<int>("total-objects-size"));
        this->m_fields->objectTotalLabel->setOpacity(Mod::get()->getSettingValue<int>("total-objects-opacity"));;
        this->m_fields->objectTotalLabel->setTag(1001);

        this->m_fields->triggerTotalLabel = CCLabelBMFont::create(
            ("Total Triggers: " + std::to_string(totalTriggers)).c_str(),
            "bigFont.fnt");
        this->m_fields->triggerTotalLabel->setPosition({5, CCDirector::sharedDirector()->getWinSize().height - (Mod::get()->getSettingValue<int>("total-triggers-delta-pos")*10)});
        this->m_fields->triggerTotalLabel->setAnchorPoint({0, 1});
        this->m_fields->triggerTotalLabel->setScale(0.05f * Mod::get()->getSettingValue<int>("total-triggers-size"));
        this->m_fields->triggerTotalLabel->setOpacity(Mod::get()->getSettingValue<int>("total-triggers-opacity"));
        this->m_fields->triggerTotalLabel->setTag(1002);

        this->m_fields->objectActiveLabel = CCLabelBMFont::create(
            ("Active Objects: " + std::to_string(this->m_activeObjects)).c_str(),
            "bigFont.fnt"
        );
        this->m_fields->objectActiveLabel->setPosition({5, CCDirector::sharedDirector()->getWinSize().height - (Mod::get()->getSettingValue<int>("active-objects-delta-pos")*10)});
        this->m_fields->objectActiveLabel->setAnchorPoint({0, 1});
        this->m_fields->objectActiveLabel->setScale(0.05f * Mod::get()->getSettingValue<int>("active-objects-size"));
        this->m_fields->objectActiveLabel->setOpacity(Mod::get()->getSettingValue<int>("active-objects-opacity"));
        this->m_fields->objectActiveLabel->setTag(1003);

        this->m_fields->particleActiveLabel = CCLabelBMFont::create(
            ("Active Particles: " + std::to_string(this->m_particleCount)).c_str(),
            "bigFont.fnt");
        this->m_fields->particleActiveLabel->setPosition({5, CCDirector::sharedDirector()->getWinSize().height - (Mod::get()->getSettingValue<int>("active-particles-delta-pos")*10)});
        this->m_fields->particleActiveLabel->setAnchorPoint({0, 1});
        this->m_fields->particleActiveLabel->setScale(0.05f * Mod::get()->getSettingValue<int>("active-particles-size"));
        this->m_fields->particleActiveLabel->setOpacity(Mod::get()->getSettingValue<int>("active-particles-opacity"));
        this->m_fields->particleActiveLabel->setTag(1004);


        // Добавление текста на сцену
        this->addChild(this->m_fields->objectTotalLabel, 101);
        this->addChild(this->m_fields->triggerTotalLabel, 101);
        this->addChild(this->m_fields->objectActiveLabel, 101);
        this->addChild(this->m_fields->particleActiveLabel, 101);
    }

    void updateActiveObjects() {
        if (this->m_fields->objectActiveLabel) {
            this->m_fields->objectActiveLabel->setString(("Active Objects: " + std::to_string(this->m_activeObjects)).c_str());
        }
    }
    void updateActiveParticles() {
        if (this->m_fields->particleActiveLabel) {
            this->m_fields->particleActiveLabel->setString(("Active Particles: " + std::to_string(this->m_particleCount)).c_str());
        }
    }

    void onQuit() {
        if (this->m_fields->objectTotalLabel) {
            this->removeChildByTag(1001);
        }
        if (this->m_fields->triggerTotalLabel) {
            this->removeChildByTag(1002);
        }
        if (this->m_fields->objectActiveLabel) {
            this->removeChildByTag(1003);
        }
        if (this->m_fields->particleActiveLabel) {
            this->removeChildByTag(1004);
        }
        PlayLayer::onQuit();
    }

    void updateInfoLabel() {
        updateActiveObjects();
        updateActiveParticles();
    }
};
