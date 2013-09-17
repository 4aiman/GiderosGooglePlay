<h1>Plugin Reference API</h1>
<style>
.ios{
	color: green;
}
</style>
<h2>Methods</h2>
<p><strong>Methods and properties that are supported by both Android ans iOS are marked as <span class='ios'>green</span></strong></p>
<ul>
<li class='ios'>googleplay:login() --login</li>
<li class='ios'>googleplay:logout() --logout</li>
<li>googleplay:showSettings() --show settings screen</li>
<li class='ios'>googleplay:showLeaderboard(leaderboardId) --show leaderboard screen</li>
<li class='ios'>googleplay:reportScore(leaderboardId, score [,immediate]) --post score to service</li>
<li class='ios'>googleplay:showAchievements() --show achievements screen</li>
<li class='ios'>googleplay:reportAchievement(achId [, numSteps, immediate]) --achievement unlocked or progressed by specified amount of steps of total defined steps</li>
<li class='ios'>googleplay:loadAchievements() --retrieve all defined achievemenets</li>
<li class='ios'>googleplay:loadScores(leaderboardId [,timespan, participants, maxResults]) --retrieve all scores for specific leaderboard ina specific timespan for specific participans</li>
<li class='ios'>googleplay:loadPlayerScores(leaderboardId [,timespan, participants, maxResults]) --retrieve all scores for specific leaderboard ina specific timespan for specific participans</li>
<li>googleplay:autoMatch(minPlayers, maxPlayers) --create a quick game between randomly selected players</li>
<li>googleplay:invitePlayers(minPlayers, maxPlayers) --allow user to invite players to a game</li>
<li>googleplay:joinRoom(invitationId) --joins the game you've been invited to</li>
<li>googleplay:showInvitations() --show screen for managing invitations</li>
<li>googleplay:showWaitingRoom(minPlayers) --show waiting room before the game with the list of players</li>
<li>googleplay:sendTo(playerId, data, isReliable) --send data to specific user by id</li>
<li>googleplay:sendToAll(data, isReliable) -- send to all users</li>
<li class='ios'>googleplay:getCurrentPlayer() --get your current user name</li>
<li class='ios'>googleplay:getCurrentPlayerId() --get your current user id</li>
<li class='ios'>googleplay:getCurrentPlayerId() --get your current user id</li>
<li>googleplay:getAllPlayers() --retrieve information (id and name) for all users involved in game</li>
<li class='ios'>googleplay:loadState(key) --load app state from slot key from the cloud</li>
<li class='ios'>googleplay:updateState(key, data[, immediate]) --update app state for slot key with data bool immediate if it needs to be saved immediately</li>
<li class='ios'>googleplay:deleteState(key) --delete app state for slot key</li>
<li class='ios'>googleplay:resolveState(key, version, data) --resolve state conflict for slot key with version and data</li>
</ul>

<h2>Properties</h2>
<ul>
<li class='ios'>GooglePlay.UNLOCKED --achievement state unlocked</li>
<li class='ios'>GooglePlay.REVEALED --achievement state available to user</li>
<li class='ios'>GooglePlay.HIDDEN   --achievement state unknown to user </li>
</ul>
<ul>
<li class='ios'>GooglePlay.ALL_TIME --leaderboard timespan all time</li>
<li class='ios'>GooglePlay.WEEK     --leaderboard timespan week</li>
<li class='ios'>GooglePlay.TODAY    --leaderboard timespan today</li>
</ul>
<ul>
<li class='ios'>GooglePlay.FRIENDS  --leaderboard participants</li>
<li class='ios'>GooglePlay.ALL_PLAYERS --leaderboard participants</li>
</ul>
<h2>Events</h2>

<h3>Game Events</h3>
<ul>
<li>Event.DATA_RECEIVED
<ul>
	<li>event.sender</li>
	<li>event.data</li>
</ul>
</li>
<li>Event.GAME_STARTED</li>
<li class='ios'>Event.REPORT_ACHIEVEMENT_COMPLETE
<ul>
	<li class='ios'>event.achievementId</li>
</ul>
</li>
<li class='ios'>Event.LOAD_ACHIEVEMENTS_COMPLETE
<ul>
	<li class='ios'>event.achievements</li>
	<li class='ios'>event.achievements[].id</li>
	<li class='ios'>event.achievements[].name</li>
	<li class='ios'>event.achievements[].description</li>
	<li class='ios'>event.achievements[].status</li>
	<li class='ios'>event.achievements[].currentSteps</li>
	<li class='ios'>event.achievements[].totalSteps</li>
	<li class='ios'>event.achievements[].lastUpdate</li>
</ul>
</li>
<li class='ios'>Event.REPORT_SCORE_COMPLETE</li>
<li class='ios'>Event.LOAD_SCORES_COMPLETE
<ul>
	<li class='ios'>event.name</li>
	<li class='ios'>event.leaderboardId</li>
	<li class='ios'>event.scores</li>
	<li class='ios'>event.scores[].name</li>
	<li class='ios'>event.scores[].timestamp</li>
	<li class='ios'>event.scores[].score</li>
	<li class='ios'>event.scores[].rank</li>
	<li class='ios'>event.scores[].playerId</li>
</ul>
</li>
</ul>

<h3>Autorization Events</h3>
<ul>
<li class='ios'>Event.LOGIN_ERROR</li>
<li class='ios'>Event.LOGIN_COMPLETE</li>
</ul>

<h3>Cloud Events</h3>
<ul>
<li class='ios'>Event.STATE_LOADED
<ul>
	<li class='ios'>event.key</li>
	<li class='ios'>event.isFresh</li>
	<li class='ios'>event.data</li>
</ul>
</li>
<li class='ios'>Event.STATE_ERROR
<ul>
	<li class='ios'>event.key</li>
</ul>
</li>
<li class='ios'>Event.STATE_CONFLICT
<ul>
	<li class='ios'>event.key</li>
	<li class='ios'>event.version</li>
	<li class='ios'>event.localData</li>
	<li class='ios'>event.serverData</li>
</ul>
</li>
<li class='ios'>Event.STATE_DELETED
<ul>
	<li class='ios'>event.key</li>
</ul>
</li>
</ul>

<h3>Room Events</h3>
<ul>
<li>Event.DISCONNECTED_FROM_ROOM
<ul>
	<li>event.roomId</li>
</ul>
</li>
<li>Event.ROOM_CREATED
<ul>
	<li>event.roomId</li>
</ul>
</li>
<li>Event.LEFT_ROOM
<ul>
	<li>event.roomId</li>
</ul>
</li>
<li>Event.ROOM_CONNECTED
<ul>
	<li>event.roomId</li>
</ul>
</li>
<li>Event.CONNECTED_TO_ROOM
<ul>
	<li>event.roomId</li>
</ul>
</li>
<li>Event.ROOM_CONNECTING
<ul>
	<li>event.roomId</li>
</ul>
</li>
<li>Event.ROOM_AUTO_MATCHING
<ul>
	<li>event.roomId</li>
</ul>
</li>
<li>Event.JOINED_ROOM
<ul>
	<li>event.roomId</li>
</ul>
</li>
<li>Event.INVITATION_RECEIVED
<ul>
	<li>event.invitationId (can be used to connect to room)</li>
</ul>
</li>
</ul>

<h3>Peer Events</h3>
<ul>
<li>Event.PEER_INVITED</li>
<li>Event.PEER_JOINED</li>
<li>Event.PEER_DISCONNECTED</li>
<li>Event.PEER_CONNECTED</li>
<li>Event.PEER_LEFT</li>
<li>Event.PEER_DECLINED</li>
</ul>