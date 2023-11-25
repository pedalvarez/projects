import Vue from 'vue'
import Router from 'vue-router'
import ReqViewer from 'components/ReqViewer'
import ErrorPage from 'components/ErrorPage'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'ReqViewer',
      component: ReqViewer
    },
    {
      path: '/error',
      name: 'ErrorPage',
      component: ErrorPage
    }
  ]
})

