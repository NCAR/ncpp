pipeline {
  agent {
     node {
        label 'CentOS9'
        }
  }
  triggers {
  pollSCM('H/15 5-22 * *')
  }
  stages {
    stage('Checkout SCM') {
      steps {
        git 'eolJenkins:ncar/ncpp'
      }
    }
    stage('Build') {
      steps {
        sh 'git submodule update --init --recursive'
        sh 'scons'
      }
    }
  }
  post {
    failure {
      emailext to: "cjw@ucar.edu janine@ucar.edu cdewerd@ucar.edu",
      subject: "Jenkinsfile ncpp build failed",
      body: "See console output attached",
      attachLog: true
    }
  }
  options {
    buildDiscarder(logRotator(numToKeepStr: '10'))
  }
}
