<template>
  <div id="app" class="container">
    <router-view></router-view>
  </div>
</template>

<script>
  require('assets/css/style.css')

  import Vue from 'vue'
  import VueMask from 'v-mask'
  import Vuelidate from 'vuelidate'
  import Toasted from 'vue-toasted'
  import {EventBus} from 'eventbus'

  Vue.use(Toasted, {
    position: 'top-center',
    duration: '2000'
  })

  Vue.use(VueMask)
  Vue.use(Vuelidate)

  export default {
    name: 'app',
    created () {
      EventBus.$on('toast-error', msg => {
        Vue.toasted.error(msg)
      })
    }
  }
</script>

<style>
  #app {
    font-family: 'Avenir', Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
    color: #2c3e50;
    margin-top: 60px;
  }
</style>

