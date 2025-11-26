#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

// Terrible code, dgaf

class $modify(CreatorLayer) {
	static void onModify(auto& self) {
		if (self.setHookPriorityAfterPost("CreatorLayer::init", "minemaker0430.gddp_integration")) {
			log::warn("Failed to set hook priority for CreatorLayer::init");
		}
	}
	bool init() {
		if(!CreatorLayer::init())
			return false;
		CCMenu* m_creatorButtonsMenu = as<CCMenu*>(this->getChildByID("creator-buttons-menu"));
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("quests-button"))->setVisible(false);
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("versus-button"))->setVisible(false);
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("map-button"))->setVisible(false);
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("daily-button"))->setVisible(false);
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("weekly-button"))->setVisible(false);
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("event-button"))->setVisible(false);
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("gauntlets-button"))->setVisible(false);
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("lists-button"))->setVisible(false);
		as<CCNode*>(m_creatorButtonsMenu->getChildByID("paths-button"))->setVisible(false);

		auto gddpBtn = as<CCMenuItemSpriteExtra*>(m_creatorButtonsMenu->getChildByID("demon-progression-button"));

		bool gddpThere = Loader::get()->isModLoaded("minemaker0430.gddp_integration") && gddpBtn;

		if (gddpThere) {
			gddpBtn->setZOrder(11);
		}

		for(int i = 0; i < m_creatorButtonsMenu->getChildrenCount(); i++) {
			auto node = as<CCMenuItemSpriteExtra*>(m_creatorButtonsMenu->getChildren()->objectAtIndex(i));
			auto sprite = node->getNormalImage();
			auto nodeID = node->getID();

			if (nodeID == "create-button")
				node->setZOrder(1);
			else if (nodeID == "saved-button")
				node->setZOrder(2);
			else if (nodeID == "scores-button")
				node->setZOrder(3);
			else if (nodeID == "map-packs-button")
				node->setZOrder(4 + gddpThere);
			else if (nodeID == "featured-button")
				node->setZOrder(5 - gddpThere);
			else if (nodeID == "search-button")
				node->setZOrder(6 + gddpThere);
		}

		AxisLayout* menuLayout = as<AxisLayout*>(m_creatorButtonsMenu->getLayout());
		menuLayout->setGap(57.81);
		menuLayout->ignoreInvisibleChildren(true);
		menuLayout->setAutoScale(false);
		menuLayout->setCrossAxisReverse(false);
		m_creatorButtonsMenu->updateLayout();
		return true;
	}
};
