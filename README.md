# Mario Kart Lounge Score Tracker
This application is written for the purposes of keeping track of scores from competitive Mario Kart events.
Each event consists of 12 players competing for the most points across 12 races.<br><br>

Typically, each event has one of the following formats:
1. FFA (every player competing for themselves)
2. 2v2 (6 teams of 2; randomly generated)
3. 3v3 (4 teams of 3; randomly generated)
4. 4v4 (3 teams of 4; randomly generated)
5. 6v6 (2 teams of 6; pre-determined)

This application will only handle the team-based formats (no FFA).

# Installation
To install the application onto your own computer, either find the "MarioKartScoreInstaller.exe" on the home page and download the executable, or [Right Click Here To Download.](https://github.com/BaoPun/MarioKartLoungeScoreTracker/blob/main/MarioKartScoreInstaller.exe)<br><br>
Follow instructions on the executable to download a folder called "Mario Kart Lounge Score Tracker" on your computer.  Note that the default location is set to "Program Files," but you may change the default location.  Once downloaded, double click the file called "MKScoreTracker.exe" to run the application.

# How to Navigate the Score Tracker
## Hotkeys
Before going through each window, there are some viable hotkeys and shortcuts you can use to navigate through the application seamlessly.
1. CTRL Q - this will quit the application.  Works for EVERY SINGLE window.
2. 2, 3, 4, or 6 - only viable for the home page section.  Pressing either of these four keys will direct you to a 2v2, 3v3, 4v4, or 6v6 format respectively.
3. ESC - viable for the team registration and point allocation sections.  Pressing ESC will redirect you to the main menu.
4. ENTER - viable for the team registration and point allocation sections.  Pressing ENTER while you are focused on the input boxes will submit the teams.

## Main Menu
Upon opening the application, you will see the following image:<br><br>
![home page](./Tutorial%20Images/home.png)
<br><br>
From here, click on either the 2v2, 3v3, 4v4, or 6v6 format buttons.<br><br>

## Team Registration
No matter what format you choose, you will see the following image:<br><br>
![team registration](./Tutorial%20Images/team_registration.png)
<br><br>
To register a team, simply enter their tags in the input box and then submit the team.<br>
However, there is one restriction: any 2 tags must not start with the same character (i.e. KT and K are not allowed to be different tags).

## Point Allocation
After registering all the teams, you will see the following image.  Example is a 2v2 format with teams Q, W, E, R, T, and Y.<br><br>
![point allocation](./Tutorial%20Images/point_allocation.png)
<br><br>
There are three different list views: one showing all of the teams, one showing how many points each team has, and one showing how many submissions are available for 1 race.
<br><br>
For example, when submitting results for 1 race using the pictured example, you cannot submit team Y for 3 different placements.
<br><br>
In the input box, when submitting results, enter the tags in order from 1st place to 12th place.  Each submitted tag will automatically update the point delta display, as well as decrementing the available submissions for that tag.  If you try to submit a placement for a tag when no more submissions are available, you will get an error message as a popup.  
<br><br>
If you want to copy that point delta display and show it to others, simply click on the "Copy Scores" button on the bottom right.
<br><br>
In the event that you have made a mistake when submitting placements for a race (for example, T was supposed to be 5th and Y was supposed to be 6th, but you accidentally submitted Y as 5th place), then you can press on the "Reset Current Race" button to undo all submitted scores for the current race.  This will also update the point delta display.  
<br><br>
Once all 12 races have been submitted, the text box will no longer be interactable.  You can choose to either quit the application or go back to the main menu.

## Version Updates
1. Added a feature to reset scores for a current race in the event that the user messes up.  Make sure to reset the race prior to entering in the 12th player.
2. Added some hotkey commands for navigating through the application more seamlessly.  
3. Entering in points for tags are now case insensitive.  Entering in 'g' will now recognize team G.  For this functionality to work, also updated tag registrations such that tags starting with the same character will no longer work.
4. Added a QoL change to bring focus back to the text boxes whenever the application leaves focus in any way (ALT TAB, clicking on a different button, etc.)
