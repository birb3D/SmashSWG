-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               11.4.2-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win64
-- HeidiSQL Version:             12.6.0.6765
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

-- Dumping structure for table swgemu.creation_attribute_limits
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

-- Dumping data for table swgemu.creation_attribute_limits: 10 rows
/*!40000 ALTER TABLE `creation_attribute_limits` DISABLE KEYS */;
INSERT INTO `creation_attribute_limits` (`male_template`, `female_template`, `min_health`, `max_health`, `min_strength`, `max_strength`, `min_constitution`, `max_constitution`, `min_action`, `max_action`, `min_quickness`, `max_quickness`, `min_stamina`, `max_stamina`, `min_mind`, `max_mind`, `min_focus`, `max_focus`, `min_willpower`, `max_willpower`, `total`) VALUES
	('bothan_male', 'bothan_female', 600, 2000, 600, 1000, 600, 800, 1200, 2600, 1200, 1500, 800, 1000, 800, 2200, 800, 1200, 600, 1000, 10800),
	('human_male', 'human_female', 800, 2200, 800, 2200, 800, 2200, 800, 2200, 800, 2200, 800, 2200, 800, 2200, 800, 2200, 800, 2200, 10800),
	('moncal_male', 'moncal_female', 600, 2000, 600, 1000, 600, 800, 600, 2000, 600, 900, 900, 1100, 1200, 2600, 1200, 1600, 900, 1300, 10800),
	('rodian_male', 'rodian_female', 600, 2000, 600, 1000, 600, 800, 600, 2400, 600, 1300, 900, 1700, 600, 2000, 600, 1000, 700, 1100, 10800),
	('trandoshan_male', 'trandoshan_female', 1100, 2500, 1200, 1600, 1400, 1600, 600, 2000, 600, 900, 600, 800, 600, 2000, 600, 1000, 600, 1200, 11100),
	('twilek_male', 'twilek_female', 600, 2000, 600, 1000, 1100, 1300, 1100, 2500, 1200, 1500, 600, 800, 800, 2200, 600, 1000, 600, 1000, 10800),
	('wookiee_male', 'wookiee_female', 1300, 2700, 1300, 1700, 900, 1100, 1000, 2400, 800, 1100, 800, 1000, 800, 2200, 900, 1300, 800, 1200, 12200),
	('zabrak_male', 'zabrak_female', 1000, 2400, 600, 1000, 600, 800, 1200, 2600, 600, 900, 600, 800, 600, 2000, 600, 1000, 1400, 1800, 10800),
	('sullustan_male', 'sullustan_female', 600, 2400, 600, 1000, 600, 800, 1200, 2800, 600, 1500, 600, 1000, 800, 2400, 800, 1200, 600, 1200, 10800),
	('ithorian_male', 'ithorian_female', 600, 2800, 600, 1200, 600, 1000, 1200, 2200, 600, 1500, 600, 1000, 800, 2600, 800, 1200, 600, 1000, 10800);
/*!40000 ALTER TABLE `creation_attribute_limits` ENABLE KEYS */;

-- Dumping structure for table swgemu.creation_profession_mods
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

-- Dumping data for table swgemu.creation_profession_mods: 7 rows
/*!40000 ALTER TABLE `creation_profession_mods` DISABLE KEYS */;
INSERT INTO `creation_profession_mods` (`profession`, `health`, `strength`, `constitution`, `action`, `quickness`, `stamina`, `mind`, `focus`, `willpower`) VALUES
	('crafting_artisan', 1200, 600, 600, 1600, 800, 600, 1800, 800, 1000),
	('combat_brawler', 2000, 1000, 800, 1600, 700, 700, 1000, 600, 600),
	('social_entertainer', 1000, 600, 600, 2000, 800, 800, 1600, 800, 800),
	('combat_marksman', 2000, 900, 600, 1600, 900, 600, 1200, 600, 600),
	('science_medic', 1200, 600, 600, 1400, 600, 600, 2000, 1000, 1000),
	('outdoors_scout', 1600, 600, 700, 1600, 800, 800, 1400, 700, 800),
	('jedi', 2000, 1000, 800, 1600, 700, 700, 1000, 600, 600);
/*!40000 ALTER TABLE `creation_profession_mods` ENABLE KEYS */;

-- Dumping structure for table swgemu.creation_racial_mods
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

-- Dumping data for table swgemu.creation_racial_mods: 10 rows
/*!40000 ALTER TABLE `creation_racial_mods` DISABLE KEYS */;
INSERT INTO `creation_racial_mods` (`male_template`, `female_template`, `health`, `strength`, `constitution`, `action`, `quickness`, `stamina`, `mind`, `focus`, `willpower`) VALUES
	('bothan_male', 'bothan_female', 0, 0, 0, 600, 600, 200, 200, 200, 0),
	('human_male', 'human_female', 200, 200, 200, 200, 200, 200, 200, 200, 200),
	('moncal_male', 'moncal_female', 0, 0, 0, 0, 0, 300, 600, 600, 300),
	('rodian_male', 'rodian_female', 0, 0, 0, 400, 400, 900, 0, 0, 100),
	('trandoshan_male', 'trandoshan_female', 500, 600, 800, 0, 0, 0, 0, 0, 200),
	('twilek_male', 'twilek_female', 0, 0, 500, 500, 600, 0, 200, 0, 0),
	('wookiee_male', 'wookiee_female', 700, 700, 300, 400, 200, 200, 200, 300, 200),
	('zabrak_male', 'zabrak_female', 400, 0, 0, 600, 0, 0, 0, 0, 800),
	('sullustan_male', 'sullustan_female', 300, 0, 0, 500, 100, 100, 400, 200, 200),
	('ithorian_male', 'ithorian_female', 800, 200, 200, 200, 0, 0, 400, 0, 0);
/*!40000 ALTER TABLE `creation_racial_mods` ENABLE KEYS */;

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
