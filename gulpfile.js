var gulp = require('gulp');
var yuidoc = require("gulp-yuidoc");
var jshint = require('gulp-jshint');
var stylish = require('jshint-stylish');

gulp.task('lint', function() {
    return gulp.src('lib/*.js')
        .pipe(jshint('.jshintrc'))
        .pipe(jshint.reporter(stylish));
});

gulp.task('doc', function() {
    gulp.src("./lib/*.js")
        .pipe(yuidoc())
        .pipe(gulp.dest("./doc"));
});

gulp.task('watch', function() {
    gulp.watch("./lib/*.js", ['lint', 'doc']);
});