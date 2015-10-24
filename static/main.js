requirejs.config({
    baseUrl: 'static/bower_components/',
    paths: { // path to your app
        app: '../',
        jquery: 'jquery'
    },
    shim: {
        'jquery': {
            exports: '$'
        },
        'jquery.imagefill': ['jquery'],
        'imagesloaded': {
            deps: ['jquery']
        },
        'imagefill': {
            deps: ['jquery', 'imagesloaded']
        }
    }
});

requirejs( [
    'imagesloaded/imagesloaded',
    'imagefill/js/jquery-imagefill',
    'jquery/dist/jquery'
]);