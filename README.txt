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
git is installed http://code.google.com/p/msysgit
some kind of LAMP stack is available

Usage:

drush dl drupal --drupal-project-rename=ohtuleht -y
cd ohtuleht
drush si --db-url=mysql://your_username:your_password@localhost:port/your_dbname -y
drush dl migrate
git clone https://github.com/kristjanjansen/ol_migrate.git sites/all/modules/ol_migrate
drush en ol_migrate -y
drush mi --all
