var gulp = require('gulp');
var yuidoc = require("gulp-yuidoc");
var jshint = require('gulp-jshint');
var mocha = require('gulp-mocha');
var stylish = require('jshint-stylish');
var gulpsync = require('gulp-sync')(gulp);
var Gitdown = require('gitdown');

gulp.task('lint', function() {
    return gulp.src('lib/*.js')
        .pipe(jshint('.jshintrc'))
        .pipe(jshint.reporter(stylish));
});

gulp.task('doc', function() {
    gulp.src("./lib/*.js")
        .pipe(yuidoc())
        .pipe(gulp.dest("./api"));
});

gulp.task('mocha', function () {
    return gulp.src('./test/*.js', {read: false})
        .pipe(mocha({reporter: 'spec'}))
        .pipe(mocha({reporter: 'progress'}));
});

gulp.task('test', gulpsync.sync(['lint', 'mocha']));


gulp.task('gitdown', function () {
    return Gitdown
        .read('.gitdown/README.md')
        .write('README.md');
});
gulp.task('watch', function() {
    gulp.watch("./lib/*.js", ['lint', 'doc']);
    gulp.watch('./.gitdown/*', ['gitdown']);
});