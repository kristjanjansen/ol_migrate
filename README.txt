Õhtuleht legacy data migration to Drupal

Prequisites for Windows:

drush is installed http://drupal.org/node/594744
git is installed http://code.google.com/p/msysgit
some kind on LAMP stack is available

Usage:

drush dl drupal --drupal-project-rename=ohtuleht -y
cd ohtuleht
drush si --db-url=mysql://your_username:your_password@localhost:port/your_dbname -y
drush dl migrate
git clone https://kristjanjansen@github.com/kristjanjansen/ol_migrate.git
drush en ol_migrate -y
drush mi --all
