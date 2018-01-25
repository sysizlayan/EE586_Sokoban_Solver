set "batchisin=%~dp0"
echo "Selenium Webdriver is installing"
pip install -U selenium
echo "Selenium DONE, BeautifulSoup is installing"
pip install beautifulsoup4
echo "BeautifulSoup DONE"

xcopy webdrivers C:\webdrivers
