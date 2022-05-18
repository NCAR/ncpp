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
    success {
      mail(to: 'cjw@ucar.edu taylort@ucar.edu', subject: 'ncpp Jenkinsfile build successful', body: 'ncpp Jenkinsfile build successful')
    }
  }
  options {
    buildDiscarder(logRotator(numToKeepStr: '10'))
  }
}
