var gulp = require('gulp');
var yuidoc = require("gulp-yuidoc");

gulp.task('default', function() {
    gulp.src("./lib/*.js")
        .pipe(yuidoc())
        .pipe(gulp.dest("./doc"));
});