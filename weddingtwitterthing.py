from flask import Flask
from flask import render_template
import logging
import sys
import thetweets

app = Flask(__name__)
rootLogger = logging.getLogger()
rootLogger.setLevel(logging.DEBUG)

ch = logging.StreamHandler(sys.stdout)
ch.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
ch.setFormatter(formatter)
rootLogger.addHandler(ch)

fileLogger = logging.FileHandler("./server.log")
fileLogger.setLevel(logging.INFO)
fileLogger.setFormatter(formatter)
rootLogger.addHandler(fileLogger)

tw = thetweets.thetweets()

@app.route('/')
def hello_world():
    global tw
    images = tw.grabATweet()
    logging.getLogger().debug("images %s" % images)
    return render_template('singleimg.html', image=images[0])

if __name__ == '__main__':
    app.run(debug=True)
