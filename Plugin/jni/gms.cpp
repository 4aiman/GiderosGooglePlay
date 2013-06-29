#include <gms.h>
#include <jni.h>
#include <stdlib.h>
#include <glog.h>

extern "C" {
JavaVM *g_getJavaVM();
JNIEnv *g_getJNIEnv();
}

class GMS
{
public:
	GMS()
	{
		gid_ = g_NextId();
		
		JNIEnv *env = g_getJNIEnv();

		jclass localClass = env->FindClass("com/giderosmobile/android/plugins/googleplaygame/GGooglePlay");
		cls_ = (jclass)env->NewGlobalRef(localClass);
		env->DeleteLocalRef(localClass);
		
		jclass class_bundle = env->FindClass("android/os/Bundle");
		clsBundle = static_cast<jclass>(env->NewGlobalRef(class_bundle));
		env->DeleteLocalRef(class_bundle);
		
		jclass class_sparse = env->FindClass("android/util/SparseArray");
		clsSparse = static_cast<jclass>(env->NewGlobalRef(class_sparse));
		env->DeleteLocalRef(class_sparse);

		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "init", "(J)V"), (jlong)this);
	}

	~GMS()
	{
		JNIEnv *env = g_getJNIEnv();

		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "cleanup", "()V"));
		
		env->DeleteGlobalRef(cls_);
		env->DeleteGlobalRef(clsBundle);
		env->DeleteGlobalRef(clsSparse);
		
		gevent_RemoveEventsWithGid(gid_);
	}
	
	bool isAvailable()
	{
		JNIEnv *env = g_getJNIEnv();
		return (bool)env->CallStaticBooleanMethod(cls_, env->GetStaticMethodID(cls_, "isAvailable", "()Z"));
	}
		
	void login()
	{
		JNIEnv *env = g_getJNIEnv();
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "login", "()V"));
	}
	
	void logout()
	{
		JNIEnv *env = g_getJNIEnv();
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "logout", "()V"));
	}
	
	void showSettings()
	{
		JNIEnv *env = g_getJNIEnv();
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "showSettings", "()V"));
	}
	
	void showLeaderboard(const char *id)
	{
		JNIEnv *env = g_getJNIEnv();
		jstring jId = env->NewStringUTF(id);
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "showLeaderboard", "(Ljava/lang/String;)V"), jId);
		env->DeleteLocalRef(jId);
	}
	
	void reportScore(const char *id, long score)
	{
		JNIEnv *env = g_getJNIEnv();
		jstring jId = env->NewStringUTF(id);
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "reportScore", "(Ljava/lang/String;J)V"), jId, (jlong)score);
		env->DeleteLocalRef(jId);
	}
	
	void showAchievements()
	{
		JNIEnv *env = g_getJNIEnv();
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "showAchievements", "()V"));
	}
	
	void reportAchievement(const char *id, int steps)
	{
		JNIEnv *env = g_getJNIEnv();
		jstring jId = env->NewStringUTF(id);
		if(steps == 0)
		{
			env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "reportAchievement", "(Ljava/lang/String;)V"), jId);
		}
		else
		{
			env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "reportAchievement", "(Ljava/lang/String;I)V"), jId, (jint)steps);
		}
		env->DeleteLocalRef(jId);
	}
	
	void loadAchievements()
	{
		JNIEnv *env = g_getJNIEnv();
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "loadAchievements", "()V"));
	}
	
	void loadScores(const char *id, int span, int collection, int maxResults )
	{
		JNIEnv *env = g_getJNIEnv();
		jstring jId = env->NewStringUTF(id);
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "loadScores", "(Ljava/lang/String;III)V"), jId, (jint)span, (jint)collection, (jint)maxResults);
		env->DeleteLocalRef(jId);
	}
	
	void loadPlayerScores(const char *id, int span, int collection, int maxResults )
	{
		JNIEnv *env = g_getJNIEnv();
		jstring jId = env->NewStringUTF(id);
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "loadPlayerScores", "(Ljava/lang/String;III)V"), jId, (jint)span, (jint)collection, (jint)maxResults);
		env->DeleteLocalRef(jId);
	}
	
	void autoMatch(int minPlayers, int maxPlayers)
	{
		JNIEnv *env = g_getJNIEnv();
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "autoMatch", "(II)V"), (jint)minPlayers, (jint)maxPlayers);
	}
	
	void invitePlayers(int minPlayers, int maxPlayers)
	{
		JNIEnv *env = g_getJNIEnv();
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "invitePlayers", "(II)V"));
	}
	
	void joinRoom(const char* id)
	{
		JNIEnv *env = g_getJNIEnv();
		jstring jId = env->NewStringUTF(id);
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "joinRoom", "(Ljava/lang/String;)V"), jId);
		env->DeleteLocalRef(jId);
	}
	
	void showInvitations()
	{
		JNIEnv *env = g_getJNIEnv();
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "showInvitations", "()V"));
	}
	
	void showWaitingRoom(int minPlayers)
	{
		JNIEnv *env = g_getJNIEnv();
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "showWaitingRoom", "(I)V"), (jint)minPlayers);
	}
	
	const char* getCurrentPlayer()
	{
		JNIEnv *env = g_getJNIEnv();
		
		jstring js = (jstring)env->CallStaticObjectMethod(cls_, env->GetStaticMethodID(cls_, "getCurrentPlayer", "()Ljava/lang/String;"));
		const char *val = env->GetStringUTFChars(js, NULL);
		return val;
	}
	
	gms_Player* getAllPlayers()
	{
		JNIEnv *env = g_getJNIEnv();
		
		jobject jmapobj = env->CallStaticObjectMethod(cls_, env->GetStaticMethodID(cls_, "getAllPlayers", "()Ljava/lang/Object;"));
		gms_Player *p = this->map2player(jmapobj);
		env->DeleteLocalRef(jmapobj);
		return p;
	}
	
	void sendTo(const char* id, const void* data, size_t size, int isReliable)
	{
		JNIEnv *env = g_getJNIEnv();
		jstring jId = env->NewStringUTF(id);
		jbyteArray jdata = env->NewByteArray(size);
		env->SetByteArrayRegion(jdata, 0, size, (const jbyte*)data);
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "sendTo", "(Ljava/lang/String;[BI)V"), jId, jdata, (jint)isReliable);
		env->DeleteLocalRef(jId);
		env->DeleteLocalRef(jdata);
	}

	void sendToAll(const void* data, size_t size, int isReliable)
	{
		JNIEnv *env = g_getJNIEnv();
		jbyteArray jdata = env->NewByteArray(size);
		env->SetByteArrayRegion(jdata, 0, size, (const jbyte*)data);
		env->CallStaticVoidMethod(cls_, env->GetStaticMethodID(cls_, "sendToAll", "([BI)V"), jdata, (jint)isReliable);
		env->DeleteLocalRef(jdata);
	}
	
	std::string mapGetStr(const char *str, jobject jsubobj)
	{
		JNIEnv *env = g_getJNIEnv();
		//get value
		jstring jStr = env->NewStringUTF(str);
		jstring jretStr = (jstring)env->CallObjectMethod(jsubobj, env->GetMethodID(clsBundle, "getString", "(Ljava/lang/String;)Ljava/lang/String;"), jStr);
		env->DeleteLocalRef(jStr);
	
		const char *retVal = env->GetStringUTFChars(jretStr, NULL);
		std::string result = retVal;
		env->ReleaseStringUTFChars(jretStr, retVal);

		return result;
	}
	
	int mapGetInt(const char *str, jobject jsubobj)
	{
		JNIEnv *env = g_getJNIEnv();
		//get value
		jstring jStr = env->NewStringUTF(str);
		int ret = (int)env->CallIntMethod(jsubobj, env->GetMethodID(clsBundle, "getInt", "(Ljava/lang/String;)I"), jStr);
		env->DeleteLocalRef(jStr);
		
		return ret;
	}
	
	struct gms_Player* map2player(jobject jmapobj)
	{
		JNIEnv *env = g_getJNIEnv();
		int size = (int)env->CallObjectMethod(jmapobj, env->GetMethodID(clsSparse, "size", "()I"));
		if(size == 0)
		{
			return NULL;
		}
		
		player.clear();
		
		for (int i = 0; i < size; i++) {
			jobject jsubobj = env->CallObjectMethod(jmapobj, env->GetMethodID(clsSparse, "valueAt", "(I)Ljava/lang/Object;"), (jint)i);
			
			gms_Player gplayer = {this->mapGetStr("id", jsubobj), this->mapGetStr("name", jsubobj)};
			
			player.push_back(gplayer);
			
			env->DeleteLocalRef(jsubobj);
		}
		
		gms_Player param = {NULL, NULL};
		player.push_back(param);
		
		return &player[0];
	}
	
	void map2achievement(jobject jmapobj)
	{
		JNIEnv *env = g_getJNIEnv();
		int size = (int)env->CallObjectMethod(jmapobj, env->GetMethodID(clsSparse, "size", "()I"));
		if(size == 0)
		{
			return;
		}
		
		achievements.clear();
		
		for (int i = 0; i < size; i++) {
			jobject jsubobj = env->CallObjectMethod(jmapobj, env->GetMethodID(clsSparse, "valueAt", "(I)Ljava/lang/Object;"), (jint)i);
			
			Achievement gach = {this->mapGetStr("id", jsubobj), this->mapGetStr("name", jsubobj), this->mapGetStr("description", jsubobj), this->mapGetInt("status", jsubobj), this->mapGetInt("lastUpdate", jsubobj), this->mapGetInt("currentSteps", jsubobj), this->mapGetInt("totalSteps", jsubobj)};
			
			achievements.push_back(gach);
			
			env->DeleteLocalRef(jsubobj);
		}
	}
	
	void map2score(jobject jmapobj)
	{
		JNIEnv *env = g_getJNIEnv();
		int size = (int)env->CallObjectMethod(jmapobj, env->GetMethodID(clsSparse, "size", "()I"));
		if(size == 0)
		{
			return;
		}
		
		scores.clear();
		
		for (int i = 0; i < size; i++) {
			jobject jsubobj = env->CallObjectMethod(jmapobj, env->GetMethodID(clsSparse, "valueAt", "(I)Ljava/lang/Object;"), (jint)i);
			
			Score gscores = {this->mapGetStr("rank", jsubobj), this->mapGetStr("score", jsubobj), this->mapGetStr("name", jsubobj), this->mapGetInt("timestamp", jsubobj)};
			
			scores.push_back(gscores);
			
			env->DeleteLocalRef(jsubobj);
		}
	}
	
	std::string MyGetStringUTFChars(JNIEnv *env, jstring jstr)
	{
		const char *str = env->GetStringUTFChars(jstr, NULL);
		std::string result = str;
		env->ReleaseStringUTFChars(jstr, str);
		return result;
	}
	
	void onSignInFailed()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_LOGIN_ERROR_EVENT, NULL, 1, this);
	}
	
	void onSignInSucceeded()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_LOGIN_COMPLETE_EVENT, NULL, 1, this);
	}
	
	void onAchievementUpdated(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_REPORT_ACHIEVEMENT_COMPLETE_EVENT, event, 1, this);
	}
	
	void onScoreSubmitted()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_REPORT_SCORE_COMPLETE_EVENT, NULL, 1, this);
	}
	
	void onAchievementsLoaded(jobject jAch)
	{
		JNIEnv *env = g_getJNIEnv();
		this->map2achievement(jAch);
		
		size_t size = sizeof(gms_Achievements);
		int count = (int)achievements.size();
		
		for (std::size_t i = 0; i < count; ++i)
		{
			size += sizeof(gms_Achievement);
			size += achievements[i].id.size() + 1;
			size += achievements[i].name.size() + 1;
			size += achievements[i].description.size() + 1;
		}
		
		// allocate it
		gms_Achievements *event = (gms_Achievements*)malloc(size);
		
		// and copy the data into it
		char *ptr = (char*)event + sizeof(gms_Achievements);
		
		event->count = count;
		event->achievements = (gms_Achievement*)ptr;
		
		ptr += achievements.size() * sizeof(gms_Achievement);
		 
		for (std::size_t i = 0; i < count; ++i)
		{	
			event->achievements[i].id = ptr;
			strcpy(ptr, achievements[i].id.c_str());
			ptr += achievements[i].id.size() + 1;
		
			event->achievements[i].name = ptr;
			strcpy(ptr, achievements[i].name.c_str());
			ptr += achievements[i].name.size() + 1;
		
			event->achievements[i].description = ptr;
			strcpy(ptr, achievements[i].description.c_str());
			ptr += achievements[i].description.size() + 1;
		
			event->achievements[i].status = achievements[i].status;
			event->achievements[i].lastUpdate = achievements[i].lastUpdate;
			event->achievements[i].currentSteps = achievements[i].currentSteps;
			event->achievements[i].totalSteps = achievements[i].totalSteps;
		}
		
		gevent_EnqueueEvent(gid_, callback_s, GMS_LOAD_ACHIEVEMENTS_COMPLETE_EVENT, event, 1, this);
	}
	
	void onLeaderboardScoresLoaded(jstring jId, jstring jName, jobject jScores)
	{
		JNIEnv *env = g_getJNIEnv();
		this->map2score(jScores);
		
		size_t size = sizeof(gms_Leaderboard);
		int count = (int)scores.size();
		
		for (std::size_t i = 0; i < count; ++i)
		{
			size += sizeof(gms_Score);
			size += scores[i].rank.size() + 1;
			size += scores[i].score.size() + 1;
			size += scores[i].name.size() + 1;
		}
		
		std::string id = MyGetStringUTFChars(env, jId);
		std::string name = MyGetStringUTFChars(env, jName);
		
		size += id.size() + 1;
		size += name.size() + 1;
		
		// allocate it
		gms_Leaderboard *event = (gms_Leaderboard*)malloc(size);
		
		// and copy the data into it
		char *ptr = (char*)event + sizeof(gms_Leaderboard);
		
		event->id = ptr;
		strcpy(ptr, id.c_str());
		ptr += id.size() + 1;
		
		event->name = ptr;
		strcpy(ptr, name.c_str());
		ptr += name.size() + 1;
		
		event->count = count;
		event->scores = (gms_Score*)ptr;
		
		for (std::size_t i = 0; i < count; ++i)
		{	
			event->scores[i].rank = ptr;
			strcpy(ptr, scores[i].rank.c_str());
			ptr += scores[i].rank.size() + 1;
			
			event->scores[i].score = ptr;
			strcpy(ptr, scores[i].score.c_str());
			ptr += scores[i].score.size() + 1;
			
			event->scores[i].name = ptr;
			strcpy(ptr, scores[i].name.c_str());
			ptr += scores[i].name.size() + 1;
		
			event->scores[i].timestamp = scores[i].timestamp;
		}
		
		gevent_EnqueueEvent(gid_, callback_s, GMS_LOAD_SCORES_COMPLETE_EVENT, event, 1, this);
	}
	
	void onGameStarted()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_GAME_STARTED_EVENT, NULL, 1, this);
	}
	
	void onInvitationReceived(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_INVITATION_RECEIVED_EVENT, event, 1, this);
	}
	
	void onJoinedRoom(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_JOINED_ROOM_EVENT, event, 1, this);
	}
	
	void onLeftRoom(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_LEFT_ROOM_EVENT, event, 1, this);
	}
	
	void onRoomConnected(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_ROOM_CONNECTED_EVENT, event, 1, this);
	}
	
	void onRoomCreated(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_ROOM_CREATED_EVENT, event, 1, this);
	}
	
	void onConnectedToRoom(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_CONNECTED_TO_ROOM_EVENT, event, 1, this);
	}
	
	void onDisconnectedFromRoom(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_DISCONNECTED_FROM_ROOM_EVENT, event, 1, this);
	}
	
	void onPeerDeclined()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_PEER_DECLINED_EVENT, NULL, 1, this);
	}
	
	void onPeerInvitedToRoom()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_PEER_INVITED_EVENT, NULL, 1, this);
	}
	
	void onPeerJoined()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_PEER_JOINED_EVENT, NULL, 1, this);
	}
	
	void onPeerLeft()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_PEER_LEFT_EVENT, NULL, 1, this);
	}
	
	void onPeersConnected()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_PEER_CONNECTED_EVENT, NULL, 1, this);
	}
	
	void onPeersDisconnected()
	{
		gevent_EnqueueEvent(gid_, callback_s, GMS_PEER_DISCONNECTED_EVENT, NULL, 1, this);
	}
	
	void onRoomAutoMatching(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_ROOM_AUTO_MATCHING_EVENT, event, 1, this);
	}
	
	void onRoomConnecting(jstring jId)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *id = env->GetStringUTFChars(jId, NULL);
		
		gms_SimpleEvent *event = (gms_SimpleEvent*)gevent_CreateEventStruct1(
			sizeof(gms_SimpleEvent),
			offsetof(gms_SimpleEvent, id), id);
	
		env->ReleaseStringUTFChars(jId, id);
		gevent_EnqueueEvent(gid_, callback_s, GMS_ROOM_CONNECTING_EVENT, event, 1, this);
	}
	
	void onDataReceived(jbyteArray jMessage, jstring jSender)
	{
		JNIEnv *env = g_getJNIEnv();
		const char *sender = env->GetStringUTFChars(jSender, NULL);
		
		size_t structSize = sizeof(gms_ReceivedEvent);
		size_t dataSize = env->GetArrayLength(jMessage);

		//gms_ReceivedEvent *event = (gms_ReceivedEvent*)malloc(structSize + dataSize);
		
		gms_ReceivedEvent *event = (gms_ReceivedEvent*)gevent_CreateEventStruct1(
			structSize + dataSize,
			offsetof(gms_ReceivedEvent, sender), sender);

		event->data = (char*)event + structSize;
		env->GetByteArrayRegion(jMessage, 0, dataSize, (jbyte*)event->data);
		event->size = dataSize;
		
		env->ReleaseStringUTFChars(jSender, sender);
		
		gevent_EnqueueEvent(gid_, callback_s, GMS_DATA_RECEIVED_EVENT, event, 1, this);
	}
	
	g_id addCallback(gevent_Callback callback, void *udata)
	{
		return callbackList_.addCallback(callback, udata);
	}
	void removeCallback(gevent_Callback callback, void *udata)
	{
		callbackList_.removeCallback(callback, udata);
	}
	void removeCallbackWithGid(g_id gid)
	{
		callbackList_.removeCallbackWithGid(gid);
	}

private:
	static void callback_s(int type, void *event, void *udata)
	{
		((GMS*)udata)->callback(type, event);
	}

	void callback(int type, void *event)
	{
		callbackList_.dispatchEvent(type, event);
	}

private:
	gevent_CallbackList callbackList_;

private:
	jclass cls_;
	jclass clsBundle;
	jclass clsSparse;
	std::vector<gms_Player> player;
	std::vector<Achievement> achievements;
	std::vector<Score> scores;
	g_id gid_;
};

extern "C" {

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onSignInFailed(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onSignInFailed();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onSignInSucceeded(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onSignInSucceeded();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onAchievementUpdated(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onAchievementUpdated(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onScoreSubmitted(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onScoreSubmitted();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onAchievementsLoaded(JNIEnv *env, jclass clz, jobject ach, jlong data)
{
	((GMS*)data)->onAchievementsLoaded(ach);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onLeaderboardScoresLoaded(JNIEnv *env, jclass clz, jstring id, jstring name, jstring scores, jlong data)
{
	((GMS*)data)->onLeaderboardScoresLoaded(id, name, scores);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onGameStarted(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onGameStarted();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onInvitationReceived(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onInvitationReceived(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onJoinedRoom(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onJoinedRoom(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onLeftRoom(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onLeftRoom(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onRoomConnected(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onRoomConnected(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onRoomCreated(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onRoomCreated(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onConnectedToRoom(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onConnectedToRoom(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onDisconnectedFromRoom(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onDisconnectedFromRoom(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onPeerDeclined(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onPeerDeclined();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onPeerInvitedToRoom(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onPeerInvitedToRoom();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onPeerJoined(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onPeerJoined();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onPeerLeft(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onPeerLeft();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onPeersConnected(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onPeersConnected();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onPeersDisconnected(JNIEnv *env, jclass clz, jlong data)
{
	((GMS*)data)->onPeersDisconnected();
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onRoomAutoMatching(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onRoomAutoMatching(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onRoomConnecting(JNIEnv *env, jclass clz, jstring id, jlong data)
{
	((GMS*)data)->onRoomConnecting(id);
}

void Java_com_giderosmobile_android_plugins_googleplaygame_GGooglePlay_onDataReceived(JNIEnv *env, jclass clz, jbyteArray message, jstring sender, jlong data)
{
	((GMS*)data)->onDataReceived(message, sender);
}

}

static GMS *s_gms = NULL;

extern "C" {

void gms_init()
{
	s_gms = new GMS;
}

void gms_cleanup()
{
	delete s_gms;
	s_gms = NULL;
}

bool gms_isAvailable()
{
	return s_gms->isAvailable();
}

void gms_login()
{
	s_gms->login();
}

void gms_logout()
{
	s_gms->logout();
}

void gms_showSettings()
{
	s_gms->showSettings();
}

void gms_showLeaderboard(const char *id)
{
	s_gms->showLeaderboard(id);
}

void gms_reportScore(const char *id, long score)
{
	s_gms->reportScore(id, score);
}

void gms_showAchievements()
{
	s_gms->showAchievements();
}

void gms_reportAchievement(const char *id, int steps)
{
	s_gms->reportAchievement(id, steps);
}

void gms_loadAchievements()
{
	s_gms->loadAchievements();
}

void gms_loadScores(const char *id, int span, int collection, int maxResults)
{
	s_gms->loadScores(id, span, collection, maxResults);
}

void gms_loadPlayerScores(const char *id, int span, int collection, int maxResults)
{
	s_gms->loadPlayerScores(id, span, collection, maxResults);
}

void gms_autoMatch(int minPlayers, int maxPlayers)
{
	s_gms->autoMatch(minPlayers, maxPlayers);
}

void gms_invitePlayers(int minPlayers, int maxPlayers)
{
	s_gms->invitePlayers(minPlayers, maxPlayers);
}

void gms_joinRoom(const char* id)
{
	s_gms->joinRoom(id);
}

void gms_showInvitations()
{
	s_gms->showInvitations();
}

void gms_showWaitingRoom(int minPlayers)
{
	s_gms->showWaitingRoom(minPlayers);
}

void gms_sendTo(const char* id, const void* data, size_t size, int isReliable)
{
	s_gms->sendTo(id, data, size, isReliable);
}

void gms_sendToAll(const void* data, size_t size, int isReliable)
{
	s_gms->sendToAll(data, size, isReliable);
}

const char* gms_getCurrentPlayer()
{
	return s_gms->getCurrentPlayer();
}

gms_Player* gms_getAllPlayers()
{
	return s_gms->getAllPlayers();
}

g_id gms_addCallback(gevent_Callback callback, void *udata)
{
	return s_gms->addCallback(callback, udata);
}

void gms_removeCallback(gevent_Callback callback, void *udata)
{
	s_gms->removeCallback(callback, udata);
}

void gms_removeCallbackWithGid(g_id gid)
{
	s_gms->removeCallbackWithGid(gid);
}

}
