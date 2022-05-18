pipeline {
  agent any
  triggers {
  pollSCM('H H * * *')
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
      mail(to: 'cjw@ucar.edu taylort@ucar.edu', subject: 'ncpp Jenkinsfile build failed', body: 'ncpp Jenkinsfile build failed')
    }
  }
  options {
    buildDiscarder(logRotator(numToKeepStr: '10'))
  }
}
