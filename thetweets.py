import yaml
import logging
import twitter

class thetweets:
    def __init__(self):
        self.logger = logging.getLogger("thetweets")
        with open("config-local.yml", 'r') as cfgFile:
            cfgYml = yaml.load(cfgFile)

            self.key = cfgYml['twitter']['key']
            self.secret = cfgYml['twitter']['secret']
            self.accessKey = cfgYml['twitter']['accessKey']
            self.accessSecret = cfgYml['twitter']['accessSecret']
            self.hashtag = cfgYml['twitter']['hashtag']
            self.logger.debug("found twitter key as %s" % self.key)
            self.logger.info("listening for tweets with hashtag %s" % self.hashtag)

        self.api = twitter.Api(consumer_key=self.key,
                               consumer_secret=self.secret,
                               access_token_key=self.accessKey,
                               access_token_secret=self.accessSecret)

    def checkCreds(self):
        return "%s" % self.api.VerifyCredentials()

    def grabATweet(self):
        return "%s" % self.api.GetSearch(term=self.hashtag)