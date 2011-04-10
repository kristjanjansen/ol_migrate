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

drush is installed http://drupal.org/node/594744
drush make is installed: drush dl drush_make
git is installed http://code.google.com/p/msysgit
some kind of LAMP stack is available

Usage:

git clone https://github.com/kristjanjansen/ol_make.git
drush make ol_make/ol.make ol_webroot
cd ol_webroot
drush site-install minimal --db-url=mysql://username:password@localhost:port/dbname -y
drush pm-enable seven ol_features -y
drush migrate-import --all
