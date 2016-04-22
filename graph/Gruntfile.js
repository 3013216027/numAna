module.exports = function(grunt) {

  // Project configuration.
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    uglify: {
      options: {
        mangle: {
          except: ['d3']
        },
        banner: '/*! <%= pkg.name %> - v<%= pkg.version %> - '
          + '<%= grunt.template.today("yyyy-mm-dd") %> */',
      },
      my_target: {
        files: {
          //'build/js/main.js': ['src/d3.js', 'src/main.js']
          'build/js/main.js': ['src/main.js']
        }
      }
    },
    watch: {
      scripts: {
        files: ['src/main.js'],
        tasks: ['uglify'],
        options: {
          spawn: false,
        },
      },
      css: {
        files: ['src/*.css'],
        tasks: ['cssmin'],
        options: {
          spawn: false,
        }
      }
    },
    cssmin: {
      options: {
        shorthandCompacting: false,
        roundingPrecision: -1
      },
      target: {
        files: {
          'build/css/main.css': ['src/style.css']
        }
      }
    },
    concat: {
      options: {
        banner: '/*! <%= pkg.name %> - v<%= pkg.version %> - '
          + '<%= grunt.template.today("yyyy-mm-dd") %> */',
      },
      basic: {
        src: ['src/main.js'],
        dest: 'build/main.js',
      },
    },
  });

  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-cssmin');
  grunt.loadNpmTasks('grunt-contrib-concat');

  grunt.registerTask('default', ['uglify', 'cssmin', 'watch']);

};