DROP TABLE IF EXISTS `creation_profession_mods`;
CREATE TABLE IF NOT EXISTS `creation_profession_mods` (
  `profession` varchar(18) DEFAULT NULL,
  `health` int(10) unsigned DEFAULT NULL,
  `strength` int(10) unsigned DEFAULT NULL,
  `constitution` int(10) unsigned DEFAULT NULL,
  `action` int(10) unsigned DEFAULT NULL,
  `quickness` int(10) unsigned DEFAULT NULL,
  `stamina` int(10) unsigned DEFAULT NULL,
  `mind` int(10) unsigned DEFAULT NULL,
  `focus` int(10) unsigned DEFAULT NULL,
  `willpower` int(10) unsigned DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;



INSERT INTO `creation_profession_mods` (`profession`,`health`,`strength`,`constitution`,`action`,`quickness`,`stamina`,`mind`,`focus`,`willpower`) VALUES
('crafting_artisan',1200,900,900,1600,1200,900,1800,1200,1500),
('combat_brawler',2000,1500,1200,1600,1050,1050,1000,900,900),
('social_entertainer',1000,900,900,2000,1200,1200,1600,1200,1200),
('combat_marksman',2000,1350,900,1600,1350,1000,1200,900,900),
('science_medic',1200,900,900,1400,900,900,2000,1500,1500),
('outdoors_scout',1600,900,1050,1600,1200,1200,1400,1050,1200),
('jedi',2000,1500,1200,1600,1050,1050,1000,900,900);

DROP TABLE IF EXISTS `creation_attribute_limits`;
CREATE TABLE IF NOT EXISTS `creation_attribute_limits` (
  `male_template` varchar(15) DEFAULT NULL,
  `female_template` varchar(17) DEFAULT NULL,
  `min_health` int(10) unsigned DEFAULT NULL,
  `max_health` int(10) unsigned DEFAULT NULL,
  `min_strength` int(10) unsigned DEFAULT NULL,
  `max_strength` int(10) unsigned DEFAULT NULL,
  `min_constitution` int(10) unsigned DEFAULT NULL,
  `max_constitution` int(10) unsigned DEFAULT NULL,
  `min_action` int(10) unsigned DEFAULT NULL,
  `max_action` int(10) unsigned DEFAULT NULL,
  `min_quickness` int(10) unsigned DEFAULT NULL,
  `max_quickness` int(10) unsigned DEFAULT NULL,
  `min_stamina` int(10) unsigned DEFAULT NULL,
  `max_stamina` int(10) unsigned DEFAULT NULL,
  `min_mind` int(10) unsigned DEFAULT NULL,
  `max_mind` int(10) unsigned DEFAULT NULL,
  `min_focus` int(10) unsigned DEFAULT NULL,
  `max_focus` int(10) unsigned DEFAULT NULL,
  `min_willpower` int(10) unsigned DEFAULT NULL,
  `max_willpower` int(10) unsigned DEFAULT NULL,
  `total` int(10) unsigned DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

INSERT INTO `creation_attribute_limits` (`male_template`,`female_template`,`min_health`,`max_health`,`min_strength`,`max_strength`,`min_constitution`,`max_constitution`,`min_action`,`max_action`,`min_quickness`,`max_quickness`,`min_stamina`,`max_stamina`,`min_mind`,`max_mind`,`min_focus`,`max_focus`,`min_willpower`,`max_willpower`,`total`) VALUES 
('bothan_male','bothan_female',600,2000,600,1600,600,1500,1200,2600,1200,2200,800,1700,800,2200,800,2000,600,1600,13600),
('human_male','human_female',800,2200,800,3000,800,3000,800,2200,800,3000,800,3000,800,2200,800,3000,800,3000,13600),
('moncal_male','moncal_female',600,2000,600,1600,600,1500,600,2000,600,1500,900,1800,1200,2600,1200,2200,900,2200,13600),
('rodian_male','rodian_female',600,2000,600,1600,600,1500,600,2400,600,2000,900,2500,600,2000,600,1600,700,2100,13600),
('trandoshan_male','trandoshan_female',1100,2500,1200,2300,1400,2200,600,2000,600,1500,600,1500,600,2000,600,1600,600,2200,14100),
('twilek_male','twilek_female',600,2000,600,1600,1100,2000,1100,2500,1200,2500,600,1500,800,2200,600,1600,600,1600,13600),
('wookiee_male','wookiee_female',1300,2700,1300,2500,900,2000,1000,2400,800,2000,800,1600,800,2200,900,2200,800,1900,16000),
('zabrak_male','zabrak_female',1000,2400,600,1600,600,1500,1200,2600,600,1600,600,1500,600,2000,600,1600,1400,2500,13600),
('sullustan_male','sullustan_female',600,2400,600,1600,600,1500,1200,2800,600,2500,600,1600,800,2400,800,1900,600,2000,13600),
('ithorian_male','ithorian_female',600,2800,600,2000,600,1700,1200,2200,600,2500,600,1600,800,2600,800,1800,600,1600,13600);

DROP TABLE IF EXISTS `creation_racial_mods`;
CREATE TABLE IF NOT EXISTS `creation_racial_mods` (
  `male_template` varchar(15) DEFAULT NULL,
  `female_template` varchar(17) DEFAULT NULL,
  `health` int(10) unsigned DEFAULT NULL,
  `strength` int(10) unsigned DEFAULT NULL,
  `constitution` int(10) unsigned DEFAULT NULL,
  `action` int(10) unsigned DEFAULT NULL,
  `quickness` int(10) unsigned DEFAULT NULL,
  `stamina` int(10) unsigned DEFAULT NULL,
  `mind` int(10) unsigned DEFAULT NULL,
  `focus` int(10) unsigned DEFAULT NULL,
  `willpower` int(10) unsigned DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

INSERT INTO `creation_racial_mods` (`male_template`,`female_template`,`health`,`strength`,`constitution`,`action`,`quickness`,`stamina`,`mind`,`focus`,`willpower`) VALUES 
('bothan_male','bothan_female',0,0,0,600,600,500,200,500,0),
('human_male','human_female',200,300,300,200,300,300,200,300,300),
('moncal_male','moncal_female',0,0,0,0,0,600,600,600,600),
('rodian_male','rodian_female',0,0,0,600,600,900,0,0,300),
('trandoshan_male','trandoshan_female',500,800,1000,0,100,100,0,0,400),
('twilek_male','twilek_female',0,0,800,500,900,0,200,0,0),
('wookiee_male','wookiee_female',800,900,500,500,400,400,400,500,400),
('zabrak_male','zabrak_female',400,0,0,600,200,200,0,0,1000),
('sullustan_male','sullustan_female',300,0,0,500,250,250,400,350,350),
('ithorian_male','ithorian_female',800,500,500,200,0,0,400,0,0);