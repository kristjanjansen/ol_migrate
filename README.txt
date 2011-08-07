Õhtuleht legacy data migration to Drupal

Migration stages:

1. ol_migrate_csv.inc is migrating data from CVS files to temporary DB table with exact same structure
   (temporary tables are created in ol_migrate.install file). Data is not modified in any way in this step.
   Yep, we could skip this step and to straigth to CSV -> Drupal migration but this is not optimal:
   eventually we need to migrate data direclty from DB anyway - then we could just discard this step and
   run step 2 with no modifications.
2. ol_migrate_db.inc is migrating data from temporary tables to Drupal database structure, converting
   and modifying data on the way.

Requirements for Windows:

drush is installed http://drupal.org/project/drush and http://drush.ws/drush_windows_installer
drush make is installed: drush dl drush_make
some kind of LAMP stack is available

Usage:

drush make https://raw.github.com/kristjanjansen/ol_make/master/ol.make ol
cd ol
drush si minimal --db-url=mysql://your_username:your_password@localhost:port/your_databse_name -y
drush en seven ol_features -y
drush vset admin_theme seven -y
drush mi --all
